#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <vector>
#include <string>
#include <memory>

class Texture
{

	friend class ShaderProgram;
public:
	typedef std::shared_ptr<Texture> ptr;

	enum class RepeatMode
	{
		Repeat = GL_REPEAT,
		Mirror = GL_MIRRORED_REPEAT,
		ClampEdge = GL_CLAMP_TO_EDGE,
		ClampBorder = GL_CLAMP_TO_BORDER
	};

	enum class FilterMode
	{
		Nearest = GL_NEAREST,
		Linear = GL_LINEAR,
		NearestMipmapNearest = GL_NEAREST_MIPMAP_NEAREST,
		LinearMipmapNearest = GL_LINEAR_MIPMAP_NEAREST,
		NearestMipmapLinear = GL_NEAREST_MIPMAP_LINEAR,
		LinearMipmapLinear = GL_LINEAR_MIPMAP_LINEAR
	};

	Texture(std::string filename, Texture::RepeatMode wrap = RepeatMode::ClampEdge, Texture::FilterMode filter = FilterMode::Linear);
	void bind();
private:
	std::vector<unsigned char> pixels;
	unsigned int width;
	unsigned int height;

	GLuint gl_tex;

	void flip();
};
