#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <thread>
#include "gl/shader.h"

int main(int argc, char **argv)
{
    glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	glewExperimental = GL_TRUE;

	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr); // Windowed
	glfwMakeContextCurrent(window);

    glewInit();

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	float vertices[] = {
	     0.0f,  0.5f, // Vertex 1 (X, Y)
	     0.5f, -0.5f, // Vertex 2 (X, Y)
	    -0.5f, -0.5f  // Vertex 3 (X, Y)
	};

	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	const char *vshader = "#version 150 \n\
in vec2 position; \n\
\n\
void main()\n\
{\n\
    gl_Position = vec4(position, 0.0, 1.0);\n\
}";

	const char *fshader = "#version 150 \n\
out vec4 outColor; \n \
void main() \n \
{ \n \
    outColor = vec4(1.0, 1.0, 1.0, 1.0); \n \
}";
	
	Shader v(GL_VERTEX_SHADER, vshader);
	v.compile();
	Shader f(GL_FRAGMENT_SHADER, fshader);
	f.compile();

	ShaderProgram p(v, f);
	p.bind_frag(0, "outColor");
	p.link();
	p.use();

	GLint posAttrib = p.get_attrib("position");
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(posAttrib);

	while(!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	    glfwSwapBuffers(window);
	    glfwPollEvents();
	    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    		glfwSetWindowShouldClose(window, GL_TRUE);
	}

    glfwTerminate();
}
