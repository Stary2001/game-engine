#define GLEW_STATIC
#include <GL/glew.h>
#include "texture.h"
#include "lodepng.h"


Texture::Texture(std::string filename, Texture::RepeatMode wrap, Texture::FilterMode filter)
{
	unsigned int error = lodepng::decode(pixels, width, height, filename);
	if(error)
	{
		// todo.

		throw std::exception();
	}

	glGenTextures(1, &gl_tex);
	bind();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLint)wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLint)wrap);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLint)filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLint)filter);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, &pixels[0]);
}

void Texture::bind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gl_tex);
}