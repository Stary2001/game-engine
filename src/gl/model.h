#pragma once
#include "vec.h"
#include <vector>
#include <memory>

struct Vertex
{
	Vertex() {}
	Vertex(Vec3D v_) { v=v_; }
	Vertex(Vec3D v_, Vec3D n_) { v=v_; n=n_; }
	Vertex(Vec3D v_, Vec2D t_) { v=v_; t=t_; }
	Vertex(Vec3D v_, Vec3D n_, Vec2D t_) { v=v_; n=n_; t=t_; }
	Vec3D v;
	Vec3D n;
	Vec2D t;
};

inline bool operator==(const Vertex& lhs, const Vertex& rhs) 
{ return lhs.v == rhs.v && lhs.n == rhs.n && lhs.t == rhs.t; }

class Model
{
public:
	Model(std::vector<Vertex> v, std::vector<uint32_t> i);
	typedef std::unique_ptr<Model> ptr;

	void draw();
	void bind();
private:
	void init();

	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

	GLuint index_buffer;
	GLuint vertex_buffer;
};