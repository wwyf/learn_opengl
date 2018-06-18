#include "offLoader.h"

offLoader::offLoader(){
    vertices = nullptr;
    vertices_size = 0;
    indices = nullptr;
    indices_size = 0;
}
void offLoader::load_from_file(std::string off_file_name){
    ifstream off_file(off_file_name);
    char file_format[10];
    int temp;
    off_file >> file_format >> this->vertices_size >> this->indices_size >> temp;
    /* 刚刚读到的是每三个点为一组的组数 */
    // this->vertices_size *= 3;
    // this->indices_size *= 3;
    this->vertices = (float *)malloc(sizeof(float) * 10000 * 3);
    this->indices = (unsigned int *)malloc(sizeof(unsigned int) * 10000 * 3);
    
    /* 读取顶点数据 */
    int vertices_count = this->vertices_size;
    for (int i = 0; i < vertices_count; i++){
        float x,y,z;
        off_file >> x >> y >> z;
        vertices[3*i] = x/100;
        vertices[3*i+1] = y/100;
        vertices[3*i+2] = z/100;
        // cout << this->vertices[i];
    }

    /* 读取顶点索引数据 */
    for (int i = 0; i < this->indices_size; i++){
        int temp;
        off_file >> temp;
        // cout << "temp : " << temp << endl;
        float x,y,z;
        off_file >> x >> y >> z;
        indices[3*i] = x;
        indices[3*i+1] = y;
        indices[3*i+2] = z;
        // cout << endl;
    }
}
float * offLoader::get_vertices_array(){
    return this->vertices;
}
unsigned * offLoader::get_indices_array(){
    return this->indices;
}
int offLoader::get_vertices_size(){
    return this->vertices_size;

}
int offLoader::get_indices_size(){
    return this->indices_size;
}
offLoader::~offLoader(){
    free(indices);
    free(vertices);
}