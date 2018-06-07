# 计算机图形学 HW4-2 报告

模仿meshlab实现一个具有类似功能的3d模型查看工具。

[TOC]

## 1 开发环境

本作业的开发环境是MinGW，完成作业后使用vs 2017编译并提交release版。
基于GLFW第三方库进行窗口管理。

## 2 程序实现说明

### 2.1 概述

由于本程序在OPENGL核心模式下进行编程，因此实现的方法有一些复杂，下面解释一下程序的细节。

整个程序大致分为两部分说明，一部分为文件读取部分，另一部分是模型变换部分的说明。

其中在模型变换部分，由于我实现了两种模式，因此对两种模式分别讲解。

第一种模式是操作模式，在这个模式下，可以对模型进行平移，旋转等操作。

第二种模式是探索模式，该模式下， 我可以成为一个在场景中移动的摄像机，在整个场景中自动移动，并使用鼠标控制方向。

### 2.2 读取OBJ，OFF，PLY文件的实现。

在实现读取模型文件的过程中，我上网搜索过`openmesh`,`assimp`等库，这些库能够帮我完成读取这些文件的工作。由于这些文件比较简单，因此我自己实现了读取模型文件的类，而没有使用以上的库。

在这一部分，我主要说明以下两点：

1. 三个Loader类的接口说明
1. 对objLoader类的实现说明

另外两个Loader类由于与objLoader类似，就不多加赘述了。

#### 2.2.1 三种Loader类的说明

对于三种不同的模型文件，我分别使用了这三个类来对模型文件进行读取。

1. objLoader
1. offLoader
1. plyLoader

这几个类都有着类似的接口，接口可见下面`objLoader`实例代码：

```c++
class objLoader{
public:
    objLoader();
    void load_from_file(std::string obj_file_name);
    float * get_vertices_array();
    unsigned * get_indices_array();
    int get_vertices_size();
    int get_indices_size();
    ~objLoader();
private:
    float * vertices;
    unsigned int * indices;
    int vertices_size;
    int indices_size;
};
```

几个函数的功能如下表所示。

|函数名称 | 函数功能 |
|-|-|
|load_from_file | 从指定文件名中读取文件数据，将数据存储到vertices和indices数组中|
|get_vertices_array| 获取该文件的顶点数据|
|get_indeices_array| 获取该文件的顶点索引数据|
|get_vertices_size| 获取该文件的顶点数量|
|get_indeices_size| 获取该文件的顶点索引数量|

#### 2.2.2 obj文件的读取

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

因此在主程序中，我只需要如以下方式就可以绘制模型

```c++

Mesh m1 = Mesh();
m1.load_from_file("cow.obj");
m1.init_mesh_data();

/* 主渲染循环 */
while (1){
    /* 初始化着色器 */
    m1.draw();
}

```

### 2.4 操作模式

在该模式下， 我可以使用键盘和鼠标操作模型本身。具体的使用说明可见第三部分程序运行方法，这里说明了具体的实现思路。

#### 2.4.1 键盘交互实现模型的平移

我使用了以下全局变量来控制模型的平移位置。

```c++
float translation_x = 0;
float translation_y = 0;
float translation_z = -3.0f;
```

这三个量可以通过小键盘上的方向键来进行修改。可见代码中的`processInput`函数中的一部分

```c++
void processInput(GLFWwindow *window){
    /*....*/
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
    /* ... */
}
```

这几个量的改变是如何影响模型的位置的呢？我使用了` glm::translate `函数用于根据前面的全局变量计算模型矩阵。

```c++
model  = glm::translate(model, glm::vec3(translation_x, translation_y, translation_z));
model = model *  mouse_rolate;
```

该模型矩阵会在着色器中对模型顶点坐标进行平移。具体着色器的代码由于比较简单就不放上来了。

#### 2.4.2 鼠标交互实现模型的旋转

使用鼠标交互实现模型的旋转的过程中，我们需要从鼠标获取一个关键的量：鼠标按下并拖动得到的方向向量。有此方向向量才能做之后的旋转操作。因此下面主要从两方面说明我的实现：

1. 鼠标拖动方向向量的获取
2. 由方向向量得到模型旋转矩阵

为了获取该方向向量，我做了以下几个工作。

1. 设计移动鼠标回调函数，实时更新反映当前鼠标位置的全局变量`curse_x`, `curse_y`
2. 设计全局变量，内容为在按下鼠标左键时（不放开），刚按下的瞬间鼠标的位置。`curse_press_x`, `curse_press_y`
3. 通过以上的两个坐标，就可以直接得到鼠标拖动的方向向量。

具体的代码实现可见以下内容。

鼠标移动的回调函数，即鼠标一旦移动，就会调用该函数进行全局变量的更新。需要注意的一点是，鼠标的坐标与OpenGL坐标系内的坐标并不一致，因此我做了适当的转换。同时还需要说明的一点是，在鼠标没有按下的时候，会保持`curse_press_x/y`与`curse_x/y`一致。

```c++
void curse_pos_callback(GLFWwindow *window, double x, double y)
{
    // std::cout << "(pos:" << x << "," << y << ")" << std::endl;
    curse_x = 2*(x / SCR_WIDTH - 0.5);
    curse_y = 2*(0.5 - y / SCR_HEIGHT);
    if (mouse_press_flag == 0){
        curse_press_x = curse_x;
        curse_press_y = curse_y;  
    }   
}
```

当鼠标按下时，会调用以下函数，将鼠标状态标志设为1，此后`curse_press_x`, `curse_press_y`不再改变。放开鼠标后，将鼠标状态标志恢复为0。

```c++
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    /* 刚开始按下，记录坐标信息 */
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && mouse_press_flag == 0){
        cout << "mouse press!" << endl;
        mouse_press_flag = 1;
    }
    /* 刚放下鼠标后，清空标志 */
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE){
        mouse_press_flag = 0;
        curse_press_x = curse_x;
        curse_press_y = curse_y;
    }
}

```

在鼠标保持按下的时候，在主渲染循环中会计算方向和旋转角度，并得出鼠标旋转矩阵。需要说明的是，为了旋转行为的明确，我对于不同的方向向量，会控制在只绕着x轴和y轴旋转，而不是任意角度。因此在代码中，增加了一个if语句判断旋转的轴。

```c++

if (mouse_press_flag){
    // 转换视角
    float angle = sqrt( (curse_x-curse_press_x/2) *(curse_x-curse_press_x/2) + 
                       (curse_y-curse_press_y/2) * (curse_y-curse_press_y/2)  );
    if (abs(curse_y - curse_press_y) > abs(curse_x - curse_press_x)){
        mouse_rolate = glm::rotate(mouse_rolate, 
                                   angle/1000 * (curse_y - curse_press_y), 
                                   glm::vec3(1.0f  , 0.0f, 0.0f)  );
    }
    else {
        mouse_rolate = glm::rotate(mouse_rolate,
                                   angle/1000 * (curse_x - curse_press_x),
                                   glm::vec3(0, 1.0f, 0.0f)  );
            }
        }
```

在之后，鼠标旋转矩阵`mouse_rolate`会与模型矩阵相乘，以将旋转的结果施加到模型上。

```c++
model = model *  mouse_rolate;
```

### 2.5 探索模式

在探索模式中，我可以成为一个在场景中游走的摄像机，使用方向键和鼠标进行操控摄像机的位置和角度，对模型进行一个深入的观察。

具体的实现中，我实现了一个照相机类，通过键盘和鼠标的操作修改一些全局变量，并将相应的参数传递给照相机类，即可实现摄像机的自由移动。

#### 2.5.1 对摄像机类的简要说明

摄像机类提供了以下接口，这些接口中，可通过输入键盘的操作实现平移，也可出入鼠标的操作实现改变视角。

```c++
class Camera{
public:
    Camera();
    glm::mat4 get_view_matrix();
    void process_keyboard_input(camera_movement_t);
    void process_mouse_movement(float x_offset, float y_offset);
    void update_delta_time(float new_delta_time);
    void reflesh();
private:
    glm::mat4 view_matrix;
    glm::vec3 camera_pos;
    glm::vec3 camera_front;
    glm::vec3 camera_up;
    glm::vec3 world_up;
    float delta_time;
    float yaw;
    float pitch;
};
```

#### 2.5.2 键盘实现摄像仪移动

以按下W键之后运行的代码为例，说明实现的思路。

1. 根据按下的按键，给键盘类中的process_keyboard_input传入不同的参数。

   1. ```c++
      if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
          my_camera.process_keyboard_input(FORWARD);
      }
      ```

2. 摄像机类中，根据传入的参数，对摄像机的位置做出一定的调整，其中camera_front为面向摄像机前方的向量，通过加减该向量，即可实现前进和后退。

   1. ```c++
      void Camera::process_keyboard_input(camera_movement_t cm){
          float camera_speed = 0.5f * this->delta_time;
          switch (cm){
              case FORWARD:
                  camera_pos += camera_speed * camera_front;
                  break;
              case BACKWARD:
                  camera_pos -= camera_speed * camera_front;
                  break;
              case LEFT:
      			/* 省略一部分内容 */
              default:
                  break;
          }
          return ;
      }
      ```

#### 2.5.3 鼠标实现视角改变

1. 实时获取鼠标位置的改变，给摄像机类中的`process_mouse_movement `函数传入鼠标坐标的变化量。

   1. ```c++
       else {
           /* 不是第一次，每一次都计算与上一帧的鼠标位置差异，并将该差异传入照相机中，修改照相机角度 */
           delta_x = curse_x - last_x;
           delta_y = last_y - curse_y; /* 注意y是相反的 */
           last_x = curse_x;
           last_y = curse_y;
           if (mode_toggle){
           my_camera.process_mouse_movement(delta_x, delta_y);
       }
       ```

   2. 

2. 根据鼠标坐标的变化量，计算摄像机的改变的偏移角和俯仰角，进而更新摄像机的前向量和上向量，从而确定摄像机的所有参数。

   1. ```c++
      void Camera::process_mouse_movement(float x_offset, float y_offset){
          // std::cout << x_offset << "   " << y_offset << std::endl;
          this->pitch -= y_offset * 1;
          this->yaw += x_offset * 1;
          if(pitch > 89.0f)
              pitch = 89.0f;
          if(pitch < -89.0f)
              pitch = -89.0f;
          glm::vec3 front = glm::vec3(1.0f);
          front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
          front.y = sin(glm::radians(pitch));
          front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
          camera_front = glm::normalize(front);
          glm::vec3 right = glm::normalize(glm::cross(camera_front, world_up));
          camera_up = glm::normalize(glm::cross(right, camera_front));
      }
      ```


最后，在主渲染循环中，调用摄像机类的`get_view_matrix`函数，即可得到view矩阵。

1. 计算Lookat矩阵
    ```c++
    glm::mat4 Camera::get_view_matrix(){
        return glm::lookAt(camera_pos, camera_pos + camera_front, camera_up);
    }
    ```
2. 更新主渲染循环中的view矩阵
    ```c++
    view = my_camera.get_view_matrix();
    ```

## 3 程序运行方法

### 3.1 编译方法

在代码目录中，可使用cmake工具进行编译。

### 3.2 运行方法

重点：在命令行下调用该程序时，第一个参数是模型文件名称。若无名称则默认为"cow.obj"。

1. 通用按键
   1. 按下t键，可进行模式的切换，具体切换到的模式可以在控制台输出查看
      1. 没有处理按键抖动的情况，因此有时会出现切换不成功的情况
   2. 按下c键，可清空之前的所有操作，回到最初的状态
   3. 按下数字键1,2,3:
      1. 【1】键为flat模式
      2. 【2】键为line模式
      3. 【3】键为flat line模式
2. 操作模式（operating mode)
   1. 可以使用小键盘的方向键，对物体进行上下平移。
   2. 键盘的`j`，`k`键，可以让物体前后平移
   3. 可以使用鼠标拖动，实现物体的旋转
3. 探索模式（exploring mode)
   1. 鼠标移动直接带来视角的改变
   2. 键盘wasd四个键可以改变摄像机的水平位置。
   3. 键盘ui两键可以改变摄像机的高度。u键上升，i键下降。

## 4 在实现过程中遇到的问题

### 4.1 三维对象的线绘制错乱

![](https://lh3.googleusercontent.com/-Lxz1iMB7E3M/WxQfx8nPFwI/AAAAAAAAII8/ivN08E_-hWUNE_lJewGV2JfwTiANIyMMQCHMYCw/s0/Code_2018-06-04_01-05-10.png)

如图，在图中的牛的线似乎并不正确，有一些线去到了不应该去的地方。

在解决这个问题的过程中，我发现了自己代码的几处问题。

1. 在设置缓冲区的时候，有一个量没有乘3,导致缓冲区大小不够大，有一些点没有正常显示。
1. 在`glDrawElement`函数中，绘制点的数量错了。
1. obj文件中的索引是从1开始的，而正确的索引应该是从0开始的。在obj的读取中，将读取到的坐标减去1即可修改正确。

## 4 程序运行截图-三种绘图模式的展现

### 4.1 cow.obj

TODO:程序运行截图还需要等待实现。

### 4.2 Armadillo.off

### 4.3 cactus.ply

## 5 程序运行录屏

对三个模型文件，分别加载运行，显示键盘鼠标操作对模型的影响。

可见作业目录下的`obj.mp4`,`off.mp4`, `ply.mp4`