# 计算机图形学 HW4-2 报告

模仿meshlab实现一个具有类似功能的3d模型查看工具。

[TOC]

## 1 开发环境

本作业的开发环境是MinGW，完成作业后使用vs 2017编译并提交release版。
基于GLFW第三方库进行窗口管理。

## 2 程序实现说明

### 2.1 概述

由于本程序在OPENGL核心模式下进行编程，因此实现的方法有一些复杂，下面解释一下程序的细节。

#### 2.1.1 程序整体结构

TODO:程序整体结构，要弄一个图吧。

### 2.2 读取OBJ，OFF，PLY文件的实现。

#### 2.2.1 OBJ文件的读取

OBJ文件的读取还是比较简单的，主要通过类`objLoader`来实现。在类中，对文件进行解析，获得顶点坐标和顶点索引数据，并放入到该类中的指针对应的内存空间中。具体的实现流程和代码可见下面。

##### 实现流程

1. 先申请足两块足够大的内存空间，分别使用vertices和indices两个指针指向，用于存放顶点坐标数据和顶点索引数据
1. 对OBJ文件进行逐行解析，解析的结果存进vertices和indices对应的数组中。
1. 这些解析得到的数据，将由`Mesh`类使用用于设置缓冲区。

##### 代码展示

`objLOader`类中的代码没有办法完全放上来，因此就放了一个关键的函数。

```c++
void objLoader::load_from_file(std::string obj_file_name){
    ifstream obj_file(obj_file_name);
    this->vertices_size = 0;
    this->indices_size = 0;
    this->vertices = (float *)malloc(sizeof(float) * 10000 * 3);
    this->indices = (unsigned int *)malloc(sizeof(unsigned int) * 10000 * 3);
    while (obj_file){
        char flag;
        obj_file >> flag;
        /* 读取v开头的顶点信息 */
        if (flag == 'v'){
            float x,y,z;
            obj_file >> x >> y >> z;
            vertices[3*this->vertices_size] = x;
            vertices[3*this->vertices_size+1] = y;
            vertices[3*this->vertices_size+2] = z;
            // cout << vertices[3*this->vertices_size] << " " << vertices[3*this->vertices_size+1] << " " << vertices[3*this->vertices_size+2]  << " " << endl; 
            this->vertices_size++;
        }
        /* 读取f开头的索引信息 */
        else if (flag == 'f'){
            int x,y,z;
            obj_file >> x >> y >> z;
            indices[3*this->indices_size] = x;
            indices[3*this->indices_size+1] = y;
            indices[3*this->indices_size+2] = z;
            // cout << indices[3*this->indices_size] << " " << indices[3*this->indices_size+1] << " " << indices[3*this->indices_size+2]  << " " << endl; 
            this->indices_size++;
        }
        else {
            break;
        }
    }
}
```

#### 2.2.2 OFF文件读取

TODO:

#### 2.2.3 PLY文件读取

TODO:

### 2.3 多边形网格对象的绘制

关于网格对象的绘制，我将OpenGL的一些函数放入了类`Mesh`中来实现，保证了主程序部分代码的简洁。
该类主要提供以下接口。

```c++
class Mesh{
public:
    Mesh();
    /**
     * @brief 从文件初始化网格信息
     * @param file_name 
     */
    void load_from_file(string file_name);

    /**
     * @brief 初始化网格数据，创建VAO
     */
    void init_mesh_data();
    /**
     * @brief 绑定VAO，绘制图像
     */
    void draw();
private:
    objLoader my_obj_object;
    float * vertices;
    int vertices_size;
    unsigned int * indices;
    int indices_size;
    unsigned int VBO, VAO, EBO;
};
```

### 2.4 平移的实现-键盘交互

TODO:可能要参照教程中的，实现一个照相机才可以。我现在的实现并不好。

### 2.5 旋转的实现-鼠标交互


## 3 程序运行方法

### 3.1 编译方法

在代码目录中，可使用cmake工具进行编译。

### 3.2 运行方法

1. 可以支持平移
    1. 使用键盘的`j`，`k`键，可以靠近或远离3D对象
    1. 使用方向键，可以上下左右平移视角
1. 可以支持旋转
    1. 使用鼠标对视角进行转换即可

## 4 在实现过程中遇到的问题

### 4.1 三维对象的线绘制错乱

![](https://lh3.googleusercontent.com/-Lxz1iMB7E3M/WxQfx8nPFwI/AAAAAAAAII8/ivN08E_-hWUNE_lJewGV2JfwTiANIyMMQCHMYCw/s0/Code_2018-06-04_01-05-10.png)

如图，在图中的牛的线似乎并不正确，有一些线去到了不应该去的地方。

在解决这个问题的过程中，我发现了自己代码的几处问题。

1. 在设置缓冲区的时候，有一个量没有乘3,导致缓冲区大小不够大，有一些点没有正常显示。
1. 在`glDrawElement`函数中，绘制点的数量错了。



## 4 程序运行截图

TODO:程序运行截图还需要等待实现。

## 5 程序运行录屏

可见作业目录下的`HW4-2-meshlab.mp4`