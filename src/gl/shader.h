#pragma once
#include <string>

class ShaderException : public std::exception
{
public:
	ShaderException(std::string e) : err(e) {}
	std::string err;
};

class Shader
{
	friend class ShaderProgram;
public:
	Shader(GLenum type, std::string source);
	void compile();
	bool status();
	std::string err();
private:
	GLuint shader;
};

class ShaderProgram
{
public:
	ShaderProgram(Shader v, Shader f);
	void link();
	void use();
	void bind_frag(GLuint pos, std::string n);
	GLuint get_attrib(std::string n);
private:
	GLuint program;
};