#include <cmath>
#include <memory>
#include <vector>
#include "util.h"
#include "primitive_gen.h"

namespace PrimitiveGen
{
	std::unique_ptr<Model> rect(GLfloat x, GLfloat y, GLfloat w, GLfloat h)
	{
		std::vector<Vec3D> verts = { {x, y, 0.0f}, {x + w, y, 0.0f}, {x + w, y + h, 0.0f}, {x, y + h, 0.0f} };
		std::vector<Vec2D> uvs = { {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f} };
		std::vector<uint32_t> indices = {0, 1, 2, 0, 2, 3};
		Model::ptr m = util::make_unique<Model>(verts, uvs, indices);

		return m;
	}

	std::unique_ptr<Model> circle(GLfloat x, GLfloat y, GLfloat radius)
	{
		const int circle_sides = 60;
		std::vector<Vec3D> verts;
		std::vector<uint32_t> indices;

		int num_tris = circle_sides - 2;

		verts.resize(circle_sides);
		indices.resize(num_tris * 3);

		int i = 0;
		int j = 0;

		double frac = 2 * M_PI / circle_sides;

		for(; i < circle_sides; i++)
		{
			verts[j++] = Vec3D(x + sin(frac * i) * radius, y + cos(frac * i) * radius, 0);
		}

		i = 1;
		j = 0;

		for(; i <= num_tris; i++)
		{
			indices[j++] = 0;
			indices[j++] = i;
			indices[j++] = i+1;
		}

		Model::ptr m = util::make_unique<Model>(verts, indices);
		return m;
	}
}