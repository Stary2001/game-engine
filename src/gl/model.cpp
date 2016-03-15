#define GLEW_STATIC
#include <GL/glew.h>

#include "model.h"

void Model::init()
{
	glGenBuffers(1, &vertex_buffer);
	glGenBuffers(1, &index_buffer);

	bind();

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vec2D), &vertices[0], GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(Vec2D), &indices[0], GL_STATIC_DRAW);
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