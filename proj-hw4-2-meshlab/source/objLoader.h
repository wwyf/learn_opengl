#ifndef  _OBJLOADER_H_
#define  _OBJLOADER_H_

#include <string>
#include <iostream>  
#include <fstream>
#include <cstdlib>
using namespace std;
/**
 * @brief 读取obj文件，返回对应的顶点数组，索引数组，以及他们的大小。
 * 
 */
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

#endif // ! _OBJLOADER_H_