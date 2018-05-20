// #define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include <iostream>
#include "shader_m.h"
#include "element.h"

using namespace std;


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int small_star_flag = 1;
int big_star_flag = 1;
int revolution_flag = 1;
int shirt_flag = 0;

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
    Shader ourShader("hw3.vs", "hw3.fs");

    LLBall big_star = LLBall(0,0,0,0.5,11);

    LLBall small_star = LLBall(0,0,0,0.4,11);

    // // set up vertex data (and buffer(s)) and configure vertex attributes
    // // ------------------------------------------------------------------
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
        // 清楚Z缓冲，颜色缓冲


        // activate shader
        ourShader.use();

        // create transformations
        glm::mat4 model_big_star = glm::mat4(1.0f);
        glm::mat4 model_small_star = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        model_big_star = glm::rotate(model_big_star, float(glfwGetTime()/2), glm::vec3(0, 0, big_star_flag * 0.1f));




        float fai = (long(revolution_flag * glfwGetTime() * 100) % 1000) * (PI*2 /1000);
        // cout << fai << endl;
        double xx,yy,zz;
        get_v_vector(0,0,1,1.0,fai, xx, yy, zz);
        model_small_star = glm::translate(model_small_star, glm::vec3(xx , yy, 0));
        model_small_star = glm::rotate(model_small_star, float(glfwGetTime()), glm::vec3(0, 0, small_star_flag * 0.9f));


        // 将物体向前平移三个单位,方便观察
        view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        // view = glm::rotate(view, float(glfwGetTime()), glm::vec3(0, 0, 0.9f));
        // 转换视角
        view = glm::rotate(view, glm::radians(-65.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        // 设置投影，角度为45度
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

        ourShader.setMat4("view", view);
        ourShader.setMat4("projection", projection);
        glm::vec4 myColor = glm::vec4(0.5f, 0.9f, 0.9f, 1.0f);
        ourShader.setVec4("myColor", myColor);

        ourShader.setMat4("model", model_big_star);

        big_star.draw();

        ourShader.setMat4("model", model_small_star);

        small_star.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // // optional: de-allocate all resources once they've outlived their purpose:
    // // ------------------------------------------------------------------------
    // glDeleteVertexArrays(1, &VAO);
    // glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS){
            revolution_flag = revolution_flag > 0? -1 : 1;
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
            small_star_flag = small_star_flag > 0? -1 : 1;
    }
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