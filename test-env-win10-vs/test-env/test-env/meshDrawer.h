#ifndef _MESH_DRAWER_H_
#define _MESH_DRAWER_H_
#include <string>
#include <glad/glad.h>
#include "objLoader.h"
#include "offLoader.h"
#include "plyLoader.h"
using namespace std;

/**
 * @brief 该类可以存储和绘制网格信息
 * 
 * 注意：该类有局限性
 * 存有的数据：
 *  1. 顶点信息
 *  2. 顶点索引信息
 * 
 */
class Mesh{
public:

    Mesh();

    /**
     * @brief 从文件初始化网格信息
     * 
     * @param file_name 
     */
    void load_from_file(string file_name);


    /**
     * @brief 初始化网格数据，创建VAO
     * 
     */
    void init_mesh_data();
    
    void draw(const Shader & my_shader);


private:
    objLoader my_obj_object;
    offLoader my_off_object;
    plyLoader my_ply_object;
    float * vertices;
    int vertices_size;
    unsigned int * indices;
    int indices_size;
    unsigned int VBO, VAO, EBO;
};


#endif // !_MESH_DRAWER_H_