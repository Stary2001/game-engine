#define GLEW_STATIC
#include <GL/glew.h>
#include "texture.h"
#include "lodepng.h"
#include "util.h"

Texture::Texture(std::string filename, Texture::RepeatMode wrap, Texture::FilterMode filter)
{
	std::vector<unsigned char> png = util::read_file_bytes("placeholder.png");
	unsigned int error = lodepng::decode(pixels, width, height, png, LCT_RGBA, 8);

	flip();

	if(error)
	{
		// todo.

		throw std::exception();
	}

	glGenTextures(1, &gl_tex);
	bind();

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pixels[0]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLint)wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLint)wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLint)filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLint)filter);
	glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::bind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gl_tex);
}

void Texture::flip()
{
    const size_t pitch = width * 4;
    unsigned char *tmp = new unsigned char[pitch];
    unsigned char *low = &pixels[0];
    unsigned char *high = &pixels[(height - 1) * pitch];

    for (; low < high; low += pitch, high -= pitch) {
        memcpy(tmp, low, pitch);
        memcpy(low, high, pitch);
        memcpy(high, tmp, pitch);
    }

    delete[] tmp;
}