#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "objLoader.h"
#include "offLoader.h"
#include "shader_m.h"
#include "plyLoader.h"
#include "meshDrawer.h"
using namespace std;

extern int show_mode;

Mesh::Mesh(){
    this->my_obj_object = objLoader();
    this->my_off_object = offLoader();
    this->my_ply_object = plyLoader();
}

/**
 * @brief 从文件初始化网格信息
 * 
 * @param file_name 
 */
void Mesh::load_from_file(string file_name){
    char flag = file_name[file_name.size()-2];
    switch (flag){
        case 'b':
            this->my_obj_object.load_from_file(file_name);
            this->vertices = this->my_obj_object.get_vertices_array();
            this->indices = this->my_obj_object.get_indices_array();
            this->vertices_size = this->my_obj_object.get_vertices_size();
            this->indices_size = this->my_obj_object.get_indices_size();
            break;
        case 'l':
            this->my_ply_object.load_from_file(file_name);
            this->vertices = this->my_ply_object.get_vertices_array();
            this->indices = this->my_ply_object.get_indices_array();
            this->vertices_size = this->my_ply_object.get_vertices_size();
            this->indices_size = this->my_ply_object.get_indices_size();
            break;
        case 'f':
            this->my_off_object.load_from_file(file_name);
            this->vertices = this->my_off_object.get_vertices_array();
            this->indices = this->my_off_object.get_indices_array();
            this->vertices_size = this->my_off_object.get_vertices_size();
            this->indices_size = this->my_off_object.get_indices_size();
            break;
    }
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
void Mesh::draw(const Shader & my_shader){
    glm::vec4 myColor = glm::vec4(0.5f, 0.9f, 0.9f, 0.6f);
    switch (show_mode){
        case 0:
            // myColor = glm::vec4(0.5f, 0.9f, 0.9f, 0.6f);
            my_shader.setVec3("objectCol", glm::vec3(0.5f, 0.9f, 0.9f));
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glDrawElements(GL_TRIANGLES, this->indices_size * 3 , GL_UNSIGNED_INT, 0);
            break;
        case 1:
            my_shader.setVec3("objectCol", glm::vec3(0.5f, 0.9f, 0.9f));
            // myColor = glm::vec4(0.5f, 0.9f, 0.9f, 0.6f);
            // my_shader.setVec4("myColor", myColor);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glDrawElements(GL_TRIANGLES, this->indices_size * 3 , GL_UNSIGNED_INT, 0);
            break;
        case 2:
            myColor = glm::vec4(0.2f, 0.2f, 0.2f, 0.2f);
            my_shader.setVec4("myColor", myColor);
            glEnable(GL_POLYGON_OFFSET_FILL);//开启多边形偏移
            glPolygonOffset(1.0, 1.0);//设置偏移量，一般-1,1即可
            // ourShader.setVec4("myColor", myColor);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glDrawElements(GL_TRIANGLES, this->indices_size * 3 , GL_UNSIGNED_INT, 0);
            glDisable(GL_POLYGON_OFFSET_FILL);//关闭多边形偏移

            // glLineWidth(0.5f);
            // myColor = glm::vec4(0.5f, 0.9f, 0.9f, 0.6f);
            my_shader.setVec3("objectCol", glm::vec3(0.5f, 0.9f, 0.9f));
            // ourShader.setVec4("myColor", myColor);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glDrawElements(GL_TRIANGLES, this->indices_size * 3 , GL_UNSIGNED_INT, 0);
            break;
        default:
            break;
    }
    glBindVertexArray(this->VAO);
    /* NOTICE: 缓冲区大小注意设置正确，之前忘了乘3 */
    // cout << this->vertices[2903 * 3] << " " << this->vertices[2903 * 3+1] << " " << this->vertices[2903 * 3 + 2] << endl;
    // cout << this->indices[5803 * 3] << " " << this->indices[5803 * 3+1] << " " << this->indices[5803 * 3 + 2] << endl;
}
