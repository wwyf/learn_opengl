// #define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include <iostream>
#include "shader_m.h"
#include "camera.h"
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
float translation_z = -1.0f;


/* 模式切换, 默认为查看模式，1为探索模式 */
int mode_toggle = 0;

/* 模式切换，flat模式， */
int show_mode = 0;

/* 摄像机类，用于改变视角 */
Camera my_camera = Camera();


glm::mat4 mouse_rolate = glm::mat4(1.0f);


/* 光源位置 */
glm::vec3 lightPos = glm::vec3(1.0f);
/* 光源颜色 */
glm::vec3 lightCol = glm::vec3(1.0f,1.0f,1.0f);

int main(int argc, char* argv[])
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
    
    Mesh m1 = Mesh();
    // cout << argc << endl;
    if (argc == 1){
        m1.load_from_file("cow.obj");
    }
    else {
        m1.load_from_file(argv[1]);
    }
    m1.init_mesh_data();



    /* 计算每一帧的时间差异 */
    float delta_time = 0.0f; // 当前帧与上一帧的时间差
    float last_frame = glfwGetTime(); // 上一帧的时间

    /* 计算每一帧鼠标移动的差异 */
    float last_x = 400, last_y = 300;
    float delta_x = 0;
    float delta_y = 0;
    int first_flag = 1;
    //---------------------------------------------------
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        /* 处理鼠标 */
        if (first_flag){
            /* 如果是第一次，则更新鼠标信息，不进行视角转换 */
            last_x = curse_x;
            last_y = curse_y;
            first_flag = 0;
        }
        else {
            /* 不是第一次，每一次都计算与上一帧的鼠标位置差异，并将该差异传入照相机中，修改照相机角度 */
            delta_x = curse_x - last_x;
            delta_y = last_y - curse_y; /* 注意y是相反的 */
            last_x = curse_x;
            last_y = curse_y;
            if (mode_toggle){
                my_camera.process_mouse_movement(delta_x, delta_y);
            }
        }

        /* 计算帧延时 */
        delta_time = glfwGetTime() - last_frame;
        last_frame = glfwGetTime();
        my_camera.update_delta_time(delta_time);

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.3f, 0.3f, 0.3f, 0.5f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
        // 清除Z缓冲，颜色缓冲


        // activate shader
        ourShader.use();

        // create transformations
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::vec4 myColor = glm::vec4(0.5f, 0.9f, 0.9f, 1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        if (mode_toggle){            
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
        else{
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }

        if (mouse_press_flag){
            // 转换视角
            // cout << curse_x-curse_press_x << "   " << curse_y-curse_press_y << endl;
            float angle = sqrt( (curse_x-curse_press_x/2) *(curse_x-curse_press_x/2) + (curse_y-curse_press_y/2) * (curse_y-curse_press_y/2));
            if (abs(curse_y - curse_press_y) > abs(curse_x - curse_press_x)){
                mouse_rolate = glm::rotate(mouse_rolate, angle/1000 * (curse_press_y - curse_y), glm::vec3(1.0f  , 0.0f, 0.0f));
            }
            else {
                mouse_rolate = glm::rotate(mouse_rolate, angle/1000 * (curse_x - curse_press_x), glm::vec3(0, 1.0f, 0.0f));
            }
        }
        else {
            // mouse_rolate = glm::mat4(1.0f);
        }

        // if (mode_toggle == 0){
        // 将物体向前平移三个单位,方便观察
            model  = glm::translate(model, glm::vec3(translation_x, translation_y, translation_z));
            model = model *  mouse_rolate;
        // } 
        // else {
            view = my_camera.get_view_matrix();
        // }

        // 设置投影，角度为45度
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

        ourShader.setMat4("model", model);
        ourShader.setMat4("view", view);
        ourShader.setMat4("projection", projection);
        // ourShader.setVec4("myColor", myColor);
        ourShader.setVec3("lightPos", lightPos);
        ourShader.setVec3("lightCol", lightCol);
        ourShader.setVec3("objectCol", glm::vec3(0.2f, 0.2f, 0.2f));


        m1.draw(ourShader);

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

    if (mode_toggle){
        /* 探索模式按键 */
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
            my_camera.process_keyboard_input(LEFT);
        }

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
            my_camera.process_keyboard_input(RIGHT);
        }

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
            // translation_y += 0.001;
            my_camera.process_keyboard_input(BACKWARD);
        }

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
            // translation_y += 0.001;
            my_camera.process_keyboard_input(FORWARD);
        }
        if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS){
            // translation_y += 0.001;
            my_camera.process_keyboard_input(UP);
        }
        if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS){
            // translation_y += 0.001;
            my_camera.process_keyboard_input(DOWN);
        }
    }
    else {
        /* 操作模式设定 */
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
            translation_y += 0.001;
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
            translation_y -= 0.001;
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
            translation_x += 0.001;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
            translation_x -= 0.001;
        }

        if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS){
            translation_z += 0.0009;
        }
        if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS){
            translation_z -= 0.0009;
        }
    }


    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS){
        mode_toggle = 1- mode_toggle;
        if (mode_toggle){
            cout << "You are in exploring mode!" << endl;
        }
        else {
            cout << "You are in operating mode!" << endl;
        }
    }


    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS){
        show_mode = 0;
    }

    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS){
        show_mode = 1;
    }

    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS){
        show_mode = 2;
    }
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS){
        my_camera.reflesh();
        translation_x = 0;
        translation_y = 0;
        translation_z = -3.0f;
        mouse_rolate = glm::mat4(1.0f);
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    translation_x = 0;
    translation_y = 0;
    translation_z = -3.0f;

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
        // curse_press_x = curse_x;
        // curse_press_y = curse_y;

        // std::cout << "(pos:" << curse_x << "," << curse_y << ")" << std::endl;
        // std::cout << "(pos:" << curse_press_x << "," << curse_press_y << ")" << std::endl;
    }
    /* 刚放下鼠标后，清空标志 */
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE){
        mouse_press_flag = 0;
        curse_press_x = curse_x;
        curse_press_y = curse_y;
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
    // std::cout << "(pos:" << curse_x << "," << curse_y << ")" << std::endl;
    // std::cout << "(pos:" << curse_press_x << "," << curse_press_y << ")" << std::endl;

    // std::cout << "(pos:" << curse_x - curse_press_x << "," << curse_y-curse_press_y << ")" << std::endl;
    
}