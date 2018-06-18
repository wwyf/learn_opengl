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


/* 得到与(xv,yv,zv)垂直的一圈的点，使用时可以将fai从0-2*PI循环来获得 */
// 当x或y或z很小的时候会出问题
void get_v_vector(double xv, double yv, double zv, double r, double fai, double &x, double &y, double &z){
    double theta;
    if (xv == 0 && yv == 0 && zv == 0){
        //不允许这种情况出现
        cout << "the length of the vector must not be zero!" << endl;
        exit(-1);
    }
    if (xv != 0){
        // zv==0 上面是失效的，就换一下坐标系就好。
        // 换成在zx平面上画
        theta = atan((-xv)/(yv * cos(fai) + zv * sin(fai)));
        if (theta < 0){
            theta += PI;
        }
        (y) = r * sin(theta) * cos(fai);
        (z) = r * sin(theta) * sin(fai);
        (x) = r * cos(theta);
    }
    else if (yv != 0){
        // zv==0 上面是失效的，就换一下坐标系就好。
        // 换成在zx平面上画
        theta = atan((-yv)/(zv * cos(fai) + xv * sin(fai)));
        if (theta < 0){
            theta += PI;
        }
        (z) = r * sin(theta) * cos(fai);
        (x) = r * sin(theta) * sin(fai);
        (y) = r * cos(theta);
    }
    else if (zv != 0){
        // zv不等于0，那就在xy平面上画
        theta = atan((-zv)/(xv * cos(fai) + yv * sin(fai)));
        if (theta < 0){
            theta += PI;
        }
        (x) = r * sin(theta) * cos(fai);
        (y) = r * sin(theta) * sin(fai);
        (z) = r * cos(theta);
    }
}


/* 
这是一个在xy平面上画圆的类，可控制z深度
// 不需要控制圆的位置吧，先写一个以原点为圆心的圆
 */
class Circle{
public:
    Circle(){
        this->x = 0;
        this->y = 0;
        this->z = 0;
        this->r = 0;
        this->n = 0;
    }
    void init(double x, double y, double z, double r, double xv, double yv, double zv, int n){
        this->x = x;
        this->y = y;
        this->z = z;
        this->r = r;
        this->n = n;

        // 生成圆上n个点的坐标
        for (int i = 0; i < 3*n;  i += 3){
            //  计算累计度数，这个就是fai
            double fai = glm::radians(i/3 * (360.00/this->n));
            double x0, y0, z0;
            get_v_vector(xv, yv, zv, r, fai, x0, y0, z0);
            this->vertices[i] = x+x0;
            this->vertices[i+1] = y+y0;
            this->vertices[i+2] = z+z0;
        }

        // 生成圆上n条边对应的索引
        for (int i = 0; i < n; i++){
            this->indices[2 * i] = i;
            this->indices[2 * i + 1] = i + 1;
            if (i == n - 1){
                this->indices[2*i] = i;
                this->indices[2 * i + 1] = 0;
            }
        }
        // 创建顶点数组缓冲对象
        glGenVertexArrays(1, &this->VAO);
        glGenBuffers(1, &this->VBO);
        glGenBuffers(1, &this->EBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertices), this->vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(this->indices), this->indices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }
    void draw(){
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glBindVertexArray(this->VAO);
        glDrawElements(GL_LINE_STRIP, 2*this->n , GL_UNSIGNED_INT, 0);
    }

    void show_v(){
        for (int i = 0; i < 3 * n; i+=3){
            cout << this->vertices[i] << "," << this->vertices[i+1] << "," << this->vertices[i+2] << endl;
            // cout << "x : " << this->vertices[i] << " y : " << this->vertices[i+1] << " z : " << this->vertices[i+2] << endl;
        }
    }

    
    void show_i(){
        for (int i = 0; i < 2 * n; i+=2){
            cout << this->indices[i] << "," << this->indices[i+1] << endl;
            // cout << "1 : " << this->indices[i] << " 2 : " << this->indices[i+1] << endl;
        }
    }

private:
    double x;
    double y;
    double z;
    double r;
    int n;
    unsigned int VBO, VAO, EBO;
    // TODO:注意数组大小应为3*n个坐标值
    float vertices[1000];
    // NOTICE:注意数组大小应为2*n个坐标值
    unsigned int indices[1000];
};


/* 
这个是用来画球的类
使用很多条经纬线，共同画出一个球
 */
class LLBall{
public:
    LLBall(double x, double y, double z, double r, int n){
        this->num_v_circle = n;
        this->num_r_circle = n;
        this->x = x;
        this->y = y;
        this->z = z;
        this->r = r;
        this->init_v_circle(0,0,1);
    }

    // FIXME:对参数有一定要求，如果是（0,0,1)这种就会出事
    void init_v_circle(double xv, double yv, double zv){
        double x0, y0, z0;
        for (int i = 0; i < this->num_v_circle; i++){
            double fai =i * (PI / this->num_v_circle) ;
            get_v_vector(xv, yv, zv, 1, fai, x0, y0, z0);
            // cout << "x0 :" << x0 << " y0 : " << y0 << " z0 : " << z0 << endl;
            v_circle[i].init(0,0,0,this->r, x0, y0, z0, 150);
        }

        for (int i = 1; i <= this->num_r_circle; i++){
            double circle_z = i * (2 * this->r / (this->num_r_circle+1)) - this->r;
            cout << " " << circle_z;
            r_circle[i].init(0,0,circle_z,sqrt(this->r * this->r - abs(circle_z*circle_z)), 0, 0, 1, 150);
        }
    }


    void draw(){
        for (int i = 0; i < this->num_v_circle; i++){
            this->v_circle[i].draw();
            this->r_circle[i].draw();
            // cout << "I : " << i << "drawing!" << endl;
        }
    }

private:
    Circle v_circle[20];
    Circle r_circle[20];
    int num_v_circle;
    int num_r_circle;
    double x;
    double y;
    double z;
    double r;
};



#endif