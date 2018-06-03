// #define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include <iostream>
#include "shader_m.h"

#include "meshDrawer.h"

using namespace std;


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void curse_pos_callback(GLFWwindow *window, double x, double y);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// 按下时鼠标的光标位置
int mouse_press_flag = 0;
float curse_press_x = 0;
float curse_press_y = 0;

// 实时鼠标光标
float curse_x = 0;
float curse_y = 0;

float translation_x = 0;
float translation_y = 0;
float translation_z = 0;

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
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, curse_pos_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    /*************************************************************/
    /** 代码
    /*************************************************************/
    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader ourShader("hw4.vs", "hw4.fs");

    // Point p1 = Point(0.5,0.5);
    // Line l1 = Line(0.5,0.9);
    glm::mat4 mouse_rolate = glm::mat4(1.0f);
    Mesh m1 = Mesh();
    m1.load_from_file("cow.obj");
    m1.init_mesh_data();

    //---------------------------------------------------
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
        // 清除Z缓冲，颜色缓冲


        // activate shader
        ourShader.use();

        // create transformations
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        glm::vec4 myColor = glm::vec4(0.5f, 0.9f, 0.9f, 1.0f);


        if (mouse_press_flag){
            // 转换视角
            float angle = sqrt( (curse_x-curse_press_x/2) *(curse_x-curse_press_x/2) + (curse_y-curse_press_y/2) * (curse_y-curse_press_y/2));
            mouse_rolate = glm::rotate(mouse_rolate, angle/1000, glm::vec3((curse_y-curse_press_y)/2, curse_x-curse_press_x/2, 0.0f));
        }
        // 将物体向前平移三个单位,方便观察
        view  = glm::translate(view, glm::vec3(translation_x, translation_y, translation_z));
        view = view *  mouse_rolate;

        // 设置投影，角度为45度
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

        ourShader.setMat4("model", model);
        ourShader.setMat4("view", view);
        ourShader.setMat4("projection", projection);
        ourShader.setVec4("myColor", myColor);

        m1.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

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

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        translation_y += 0.001;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        translation_y -= 0.001;

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        translation_x += 0.001;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        translation_x -= 0.001;

    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
        translation_z += 0.0009;
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
        translation_z -= 0.0009;

    
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

/**
 * @brief 鼠标点击的回调函数
 * 
 * @param window 
 * @param button 
 * @param action 
 * @param mods 
 */
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    /* 刚开始按下，记录坐标信息 */
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && mouse_press_flag == 0){
        cout << "mouse press!" << endl;
        mouse_press_flag = 1;
        curse_press_x = curse_x;
        curse_press_y = curse_y;
    }
    /* 刚放下鼠标后，清空标志 */
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE){
        mouse_press_flag = 0;
    }

        // s1.add_point(curse_x, curse_y);
}

/**
 * @brief 鼠标移动的回调函数
 * 
 * @param window 
 * @param x 
 * @param y 
 */
void curse_pos_callback(GLFWwindow *window, double x, double y)
{
    // std::cout << "(pos:" << x << "," << y << ")" << std::endl;
    curse_x = 2*(x / SCR_WIDTH - 0.5);
    curse_y = 2*(0.5 - y / SCR_HEIGHT);
    if (mouse_press_flag == 0){
        curse_press_x = curse_x;
        curse_press_y = curse_y;  
    }
    std::cout << "(pos:" << curse_x << "," << curse_y << ")" << std::endl;
    std::cout << "(pos:" << curse_press_x << "," << curse_press_y << ")" << std::endl;

    // std::cout << "(pos:" << curse_x - curse_press_x << "," << curse_y-curse_press_y << ")" << std::endl;
    
}