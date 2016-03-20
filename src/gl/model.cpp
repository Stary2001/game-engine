#define GLEW_STATIC
#include <GL/glew.h>

#include "model.h"

Model::Model(std::vector<Vertex> v, std::vector<uint32_t> i) : vertices(v), indices(i)
{
	glGenBuffers(1, &vertex_buffer);
	glGenBuffers(1, &index_buffer);

	bind();

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), &indices[0], GL_STATIC_DRAW);
}

void Model::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
}

void Model::draw()
{
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
}