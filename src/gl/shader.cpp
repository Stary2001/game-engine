#include <string>
#include <GL/glew.h>
#include "shader.h"

Shader::Shader(GLenum type, std::string src)
{
	shader = glCreateShader(type);
	const char *c = src.c_str();
	glShaderSource(shader, 1, &c, NULL);
}

bool Shader::status()
{
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	return status == GL_TRUE;
}

void Shader::compile()
{
	glCompileShader(shader);
	if(!status())
	{
		throw ShaderException(err());
	}
}

std::string Shader::err()
{
	GLint len = 0;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
	char *buff = new char[len];

	glGetShaderInfoLog(shader, len, NULL, buff);
	std::string s = std::string(buff, len);
	delete[] buff;
	return s;
}

ShaderProgram::ShaderProgram(Shader v, Shader f)
{
	program = glCreateProgram();
	glAttachShader(program, v.shader);
	glAttachShader(program, f.shader);
}

void ShaderProgram::link()
{
	glLinkProgram(program);
}

void ShaderProgram::use()
{
	glUseProgram(program);
}

void ShaderProgram::bind_frag(GLuint pos, std::string n)
{
	glBindFragDataLocation(program, pos, n.c_str());
}

GLuint ShaderProgram::get_attrib(std::string n)
{
	return glGetAttribLocation(program, n.c_str());
}