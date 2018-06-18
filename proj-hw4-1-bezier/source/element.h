#ifndef _CIECLE_H_
#define _CIECLE_H_

// #define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include <iostream>
#define PI 3.1415629535
using namespace std;


class Point{
public:
    Point(){}
    Point(float x, float y, float z = 0){
        vertices[0] = x;
        vertices[1] = y;
        vertices[2] = z;
        this->init();
    }
    void init(){
        // 创建顶点数组缓冲对象
        glGenVertexArrays(1, &this->VAO);
        glGenBuffers(1, &this->VBO);
        glBindVertexArray(this->VAO);
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertices), this->vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }
    void draw(){
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glBindVertexArray(this->VAO);
        // glDrawElement 这个函数画不了点
        glDrawArrays(GL_POINTS,0, 1);
    }
private:
    float vertices[3]; /** 点的x,y,z 坐标 */
    GLuint VAO, VBO;
};


class Line{
public:
    Line(float x1, float y1, float z1=0, float x2=0, float y2=0, float z2=0){
        vertices[0] = x1;
        vertices[1] = y1;
        vertices[2] = z1;
        vertices[3] = x2;
        vertices[4] = y2;
        vertices[5] = z2;
        this->init();
    }

    void init(){
        // 创建顶点数组缓冲对象
        glGenVertexArrays(1, &this->VAO);
        glGenBuffers(1, &this->VBO);
        glBindVertexArray(this->VAO);
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertices), this->vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }
    void draw(){
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glBindVertexArray(this->VAO);
        // glDrawElement 这个函数画不了点
        glDrawArrays( GL_LINES, 0 , 2);
    }
private:
    float vertices[6]; /** 点的横坐标和纵坐标 */
    GLuint VAO, VBO;
};

/**
 * @brief Get the point object
 * 
 * 计算（x1,y1) (x2,y2) 两点间比例为t处的点的坐标。
 * 
 * @param x1 
 * @param y1 
 * @param x2 
 * @param y2 
 * @param t 
 * @param x 
 * @param y 
 */
void get_point(float x1, float y1, float x2, float y2, float t, float & x, float & y){
    x = x1 + (x2-x1)*t;
    y = y1 + (y2-y1)*t;
}

/**
 * @brief 绘制三次贝塞尔曲线。
 * 
 */
class Bezier{
public:
    Bezier(){
        this->num_point = 0;
    }

    /**
     * @brief 初始化三阶贝塞尔曲线
     * 
     */
    void init(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4){
        this->x1 = x1;
        this->x2 = x2;
        this->x3 = x3;
        this->x4 = x4;
        this->y1 = y1;
        this->y2 = y2;
        this->y3 = y3;
        this->y4 = y4;
        this->num_point = 0;
        float t = 0;
        float interval = 0.001; 
        while (t <= 1){
            float x11,y11;
            float x22,y22;
            float x33,y33;
            get_point(x1, y1, x2, y2, t, x11, y11);
            get_point(x2, y2, x3, y3, t, x22, y22);
            get_point(x3, y3, x4, y4, t, x33, y33);

            float x111, y111;
            float x222, y222;
            get_point(x11, y11, x22, y22, t, x111, y111);
            get_point(x22, y22, x33, y33, t, x222, y222);

            float x1111, y1111;
            get_point(x111, y111, x222, y222, t, x1111, y1111);

            vertices[3*this->num_point] = x1111;
            vertices[3*this->num_point+1] = y1111;
            vertices[3*this->num_point+2] = 0;
            this->num_point++;
            t += interval;
        }

        // 创建顶点数组缓冲对象
        glGenVertexArrays(1, &this->VAO);
        glGenBuffers(1, &this->VBO);
        glBindVertexArray(this->VAO);
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertices), this->vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }

    /**
     * @brief 绘制贝塞尔曲线。
     * 
     */
    void draw(){
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glBindVertexArray(this->VAO);
        // glDrawElement 这个函数画不了点
        glDrawArrays(GL_POINTS,0, this->num_point);
    }
private:
    float x1, y1;
    float x2, y2;
    float x3, y3;
    float x4, y4;
    float vertices[5000];
    GLuint VAO,VBO;
    int num_point;
};






/**
 * @brief 场景类，用于显示点和线
 * 
 */
class Scene{
public:
    Scene(){
        this->num_point = 0;
        this->indices[0] = 0;
        this->indices[1] = 1;
        this->indices[2] = 1;
        this->indices[3] = 2;
        this->indices[4] = 2;
        this->indices[5] = 3;
        this->my_bezier = Bezier();
    }

    /**
     * @brief 使用当前的顶点数据和索引数据更新缓冲区
     * 
     */
    void update(){
        // 创建顶点数组缓冲对象
        glGenVertexArrays(1, &this->VAO);
        glGenBuffers(1, &this->VBO);
        glBindVertexArray(this->VAO);
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertices), this->vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        if (this->is_full()){
            /* 更新本地贝塞尔曲线 */
            this->my_bezier.init(this->vertices[0], this->vertices[1],
                                this->vertices[3], this->vertices[4],
                                this->vertices[6], this->vertices[7],
                                this->vertices[9], this->vertices[10]);
        }
    }

    /**
     * @brief 在场景中增加一个点
     * 
     * @param x 
     * @param y 
     */
    void add_point(float x, float y, float z = 0){
        if (this->is_full()){
            this->num_point = 0;
        }
        this->vertices[3*this->num_point] = x;
        this->vertices[3*this->num_point+1] = y;
        this->vertices[3*this->num_point+2] = z;
        num_point++;
        this->update();
    }

    /**
     * @brief 如果场景中有四个点及以上，则视为满
     * 
     */
    int is_full(){
        return this->num_point >= 4;
    }

    /**
     * @brief 如果场景没有点，作为空
     * 
     */
    int is_empty(){
        return this->num_point == 0;
    }

    /**
     * @brief 绘图
     * 
     * 若该场景有三个点或者更少，则只画点，否则画线
     * 
     */
    void draw(){
        if (this->is_empty()){
            return ;
        }
        else if(this->is_full()){
            /* 如果满了就画线 */
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glBindVertexArray(this->VAO);
            // glDrawElement 这个函数画不了点
            glDrawArrays(GL_LINE_STRIP, 0, this->num_point);
            this->my_bezier.draw();
        }
        else {
            /* 如果没有满就画点 */
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glBindVertexArray(this->VAO);
            // glDrawElement 这个函数画不了点
            glDrawArrays(GL_POINTS,0, this->num_point);
        }
    }

    /**
     * @brief 清空场景，点数恢复至0
     * 
     */
    void clear_scene(){
        num_point = 0;
    }


private:
    float vertices[4*3]; /** 点的x,y,z 坐标， 最多4个点 */
    float indices[3*2]; /** 三条线，需要三对索引 */
    GLuint VAO, VBO, EBO;
    int num_point;
    Bezier my_bezier;
};




#endif