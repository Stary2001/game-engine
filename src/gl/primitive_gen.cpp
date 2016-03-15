#include <cmath>
#include <memory>
#include <vector>
#include "util.h"
#include "primitive_gen.h"

namespace PrimitiveGen
{
	std::unique_ptr<Model> rect(GLfloat x, GLfloat y, GLfloat w, GLfloat h)
	{
		std::vector<Vec2D> verts = { {x, y}, {x + w, y}, {x + w, y + h}, {x, y + h} };
		std::vector<uint32_t> indices = {0, 1, 2, 0, 2, 3};
		Model::ptr m = util::make_unique<Model>(verts, indices);

		return m;
	}
}