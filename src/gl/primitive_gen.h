#pragma once
#include <GL/gl.h>
#include "model.h"

namespace PrimitiveGen
{
	Model::ptr rect(GLfloat x, GLfloat y, GLfloat w, GLfloat h);
	Model::ptr circle(GLfloat x, GLfloat y, GLfloat radius);
}