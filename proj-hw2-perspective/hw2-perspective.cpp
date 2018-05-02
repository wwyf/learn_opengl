#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "shader_m.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader ourShader("hw2-perspective.vs", "hw2-perspective-surface.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // front
        -0.5f, -0.5f,  0.5f,// 左下角，0
         0.5f, -0.5f,  0.5f,// 右下角，1
        -0.5f,  0.5f,  0.5f,// 左上角，2
         0.5f,  0.5f,  0.5f,// 右上角，3
        
        // back
        -0.5f, -0.5f,  -0.5f,// 左下角，4
         0.5f, -0.5f,  -0.5f,// 右下角，5
        -0.5f,  0.5f,  -0.5f,// 左上角，6
         0.5f,  0.5f,  -0.5f,// 右上角，7
        
    };

    unsigned int indices[] = {
        0, 1, 2, // 前面左下
        2, 3, 1, // 前面右上
        4, 5, 6, // 后面
        5, 6, 7, // 后面
        // 上面：2,3,6,7
        2, 3, 6,
        6, 3, 7,
        // 下面：0,1,4,5
        0, 1, 4,
        4, 1, 5,
        // 左面：4,0,6,2
        4, 0, 6,
        6, 0, 2,
        // 右面：1,5,3,7
        1, 5, 3,
        3, 5, 7,
    };

    unsigned int VBO, VAO, EBO;
    // 创建顶点数组缓冲对象
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
        // 清楚Z缓冲，颜色缓冲


        // activate shader
        ourShader.use();

        // create transformations
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        // 旋转矩阵，实现随时间旋转
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(-0.5f, 0.5f, 0.0f));
        // 将物体向前平移三个单位,方便观察
        view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        // 设置投影，角度为45度
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        // retrieve the matrix uniform locations
        ourShader.setMat4("model", model);
        ourShader.setMat4("view", view);
        ourShader.setMat4("projection", projection);
        glm::vec4 myColor = glm::vec4(0.5f, 0.9f, 0.9f, 1.0f);
        ourShader.setVec4("myColor", myColor);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        // glDrawArrays(GL_TRIANGLES, 0, 36);

        // 做多边形偏移，以线的方式显示轮廓线
        // 修改着色器使用的颜色。
        ourShader.setVec4("myColor", glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);//将绘制模式改为线
        glEnable(GL_POLYGON_OFFSET_LINE);//开启多边形偏移
        glPolygonOffset(-4.0, -4.0);//设置偏移量，一般-1,1即可
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glDisable(GL_POLYGON_OFFSET_LINE);//关闭多边形偏移

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}