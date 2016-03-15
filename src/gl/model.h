#pragma once
#include "vec.h"
#include <memory>

class Model
{
public:
	Model(std::vector<Vec2D> v, std::vector<uint32_t> i) : vertices(v), indices(i) {}
	Model(std::vector<Vec2D> v, std::vector<Vec2D> u, std::vector<uint32_t> i) : vertices(v), uvs(u), indices(i) {}

	std::vector<Vec2D> vertices;
	std::vector<Vec2D> uvs;
	std::vector<uint32_t> indices;

	typedef std::unique_ptr<Model> ptr;
};