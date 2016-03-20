#define GLEW_STATIC
#include <GL/glew.h>

#include "model.h"

void Model::init()
{
	glGenBuffers(1, &vertex_buffer);
	glGenBuffers(1, &index_buffer);

	bind();

	buf.resize(vertices.size() * 5);
	uvs.resize(vertices.size()); // HACK: these should match anyway, but just in case

	unsigned int i = 0;
	for(; i < vertices.size(); i++)
	{
		int ofs = i * 5;
		buf[ofs] = vertices[i].x;
		buf[ofs + 1] = vertices[i].y;
		buf[ofs + 2] = vertices[i].z;
		buf[ofs + 3] = uvs[i].s;
		buf[ofs + 4] = uvs[i].t;
	}

	glBufferData(GL_ARRAY_BUFFER, buf.size() * sizeof(float), &buf[0], GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), &indices[0], GL_STATIC_DRAW);
}

void Model::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
}

void Model::draw()
{
	glDrawArrays(GL_TRIANGLES, 0, 36);
	//glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
}