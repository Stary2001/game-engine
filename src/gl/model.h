#pragma once
#include "vec.h"
#include <vector>
#include <memory>

class Model
{
public:
	Model(std::vector<Vec2D> v, std::vector<uint32_t> i) : vertices(v), indices(i) { init(); }
	Model(std::vector<Vec2D> v, std::vector<Vec2D> u, std::vector<uint32_t> i) : vertices(v), uvs(u), indices(i) { init(); }
	typedef std::unique_ptr<Model> ptr;

	void draw();
	void bind();
private:
	void init();

	std::vector<Vec2D> vertices;
	std::vector<Vec2D> uvs;
	std::vector<uint32_t> indices;

	GLuint index_buffer;
	GLuint vertex_buffer;
};