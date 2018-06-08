#ifndef _MESH_H_
#define _MESH_H_

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "shader_m.h"
using namespace std;


typedef struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	// glm::vec2 TexCoords;
}vertex_t;

typedef struct Texture {
	unsigned int id;
	string type;
}texture_t;


class Mesh {
public:
	/*  网格数据  */
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	// vector<Texture> textures;
	/*  函数  */
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices) {
		this->vertices = vertices;
		this->indices = indices;
		// this->textures = textures;
		setupMesh();
	}
	void Draw(Shader shader) {
		// 绘制网格
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
private:
	/*  渲染数据  */
	unsigned int VAO, VBO, EBO;
	/*  函数  */
	void setupMesh() {
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		/* 绑定顶点数据 */
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		/* 技巧：理解为什么能够直接取数组的指针作为参数 */
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

		/* 绑定定点索引数据 */
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		/* 技巧：同样需要理解为什么可以直接传指针 */
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
			&indices[0], GL_STATIC_DRAW);

		// 顶点位置
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		// 顶点法线
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

		/* 使用这样的一个结构体不仅能够提供可读性更高的代码，也允许我们很容易地拓展这个结构。如果我们希望添加另一个顶点属性，我们只需要将它添加到结构体中就可以了。由于它的灵活性，渲染的代码不会被破坏。 */

		glBindVertexArray(0);
	}
};

#endif // !_MESH_H_