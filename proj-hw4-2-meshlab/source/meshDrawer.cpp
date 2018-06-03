#include <string>
#include <glad/glad.h>
#include "objLoader.h"
#include "meshDrawer.h"
using namespace std;


Mesh::Mesh(){
    this->my_obj_object = objLoader();
}

/**
 * @brief 从文件初始化网格信息
 * 
 * @param file_name 
 */
void Mesh::load_from_file(string file_name){
    this->my_obj_object.load_from_file(file_name);
    this->vertices = this->my_obj_object.get_vertices_array();
    this->indices = this->my_obj_object.get_indices_array();
    this->vertices_size = this->my_obj_object.get_vertices_size();
    this->indices_size = this->my_obj_object.get_indices_size();
    cout << this->vertices_size << endl;
    cout << this->indices_size << endl;
}


/**
 * @brief 初始化网格数据，创建VAO
 * 
 */
void Mesh::init_mesh_data(){
    // 创建顶点数组缓冲对象
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    /* NOTICE: 缓冲区大小注意设置正确，之前忘了乘3 */
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * this->vertices_size * 3, this->vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    /* NOTICE: 缓冲区大小注意设置正确，之前忘了乘3 */
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * this->indices_size * 3, this->indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}
void Mesh::draw(){
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBindVertexArray(this->VAO);
    /* NOTICE: 缓冲区大小注意设置正确，之前忘了乘3 */
    glDrawElements(GL_TRIANGLES, this->indices_size * 3 , GL_UNSIGNED_INT, 0);
    // cout << this->vertices[2903 * 3] << " " << this->vertices[2903 * 3+1] << " " << this->vertices[2903 * 3 + 2] << endl;
    // cout << this->indices[5803 * 3] << " " << this->indices[5803 * 3+1] << " " << this->indices[5803 * 3 + 2] << endl;
}
