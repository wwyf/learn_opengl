#include <string>
#include <iostream>  
#include <fstream>
#include <cstdlib>
#include "objloader.h"
using namespace std;

objLoader::objLoader(){
    vertices = nullptr;
    vertices_size = 0;
    indices = nullptr;
    indices_size = 0;
}
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
            indices[3*this->indices_size] = x-1;
            indices[3*this->indices_size+1] = y-1;
            indices[3*this->indices_size+2] = z-1;
            // cout << indices[3*this->indices_size] << " " << indices[3*this->indices_size+1] << " " << indices[3*this->indices_size+2]  << " " << endl; 
            this->indices_size++;
        }
        else {
            break;
        }
    }
}
float * objLoader::get_vertices_array(){
    return this->vertices;
}
unsigned * objLoader::get_indices_array(){
    return this->indices;
}
int objLoader::get_vertices_size(){
    return this->vertices_size;
}
int objLoader::get_indices_size(){
    return this->indices_size;
}
objLoader::~objLoader(){
    free(vertices);
    free(indices);
}
