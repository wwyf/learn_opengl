#include "plyLoader.h"

plyLoader::plyLoader(){
    vertices = nullptr;
    vertices_size = 0;
    indices = nullptr;
    indices_size = 0;

}

void plyLoader::load_from_file(std::string ply_file_name){
    ifstream ply_file(ply_file_name);
    char file_format[10];
    char temp[10];
    for (int i = 0; i < 9; i++){
        ply_file >> temp; 
    }
    ply_file >> this->vertices_size;
    for (int i = 0; i < 11; i++){
        ply_file >> temp; 
    }
    ply_file >> this->indices_size;
    for (int i = 0; i < 6; i++){
        ply_file >> temp;
    }
    cout << this->vertices_size << endl;
    cout << this->indices_size << endl;
    cout << temp << endl;
    if (!temp[0] == 'e'){
        cout << "ERROR!";
    }
    this->vertices = (float *)malloc(sizeof(float) * 10000 * 3);
    this->indices = (unsigned int *)malloc(sizeof(unsigned int) * 15000 * 3);
    
    /* 读取顶点数据 */
    int vertices_count = this->vertices_size;
    for (int i = 0; i < vertices_count; i++){
        float x,y,z;
        ply_file >> x >> y >> z;
        vertices[3*i] = x;
        vertices[3*i+1] = y;
        vertices[3*i+2] = z;
        // cout << this->vertices[i];
    }

    /* 读取顶点索引数据 */
    for (int i = 0; i < this->indices_size; i++){
        int temp;
        ply_file >> temp;
        // cout << "temp : " << temp << endl;
        float x,y,z;
        ply_file >> x >> y >> z;
        indices[3*i] = x;
        indices[3*i+1] = y;
        indices[3*i+2] = z;
        // cout << endl;
    }
}
float * plyLoader::get_vertices_array(){
    return this->vertices;
}
unsigned * plyLoader::get_indices_array(){
    return this->indices;
}
int plyLoader::get_vertices_size(){
    return this->vertices_size;

}
int plyLoader::get_indices_size(){
    return this->indices_size;
}
plyLoader::~plyLoader(){
    free(indices);
    free(vertices);
}