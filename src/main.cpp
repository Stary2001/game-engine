#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <thread>
#include <memory>
#include <vector>
#include "gl/shader.h"
#include "primitive_gen.h"
#include "util.h"

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

	Model::ptr shape = PrimitiveGen::circle(0.0f, 0.0f, 0.1f);

	GLfloat screen_width = 800.0f;
	GLfloat screen_height = 600.0f;

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), screen_width / screen_height, 1.0f, 10.0f);

	glm::mat4 view = glm::lookAt(
    	glm::vec3(0.0f, 0.0f, 2.0f),
    	glm::vec3(0.0f, 0.0f, 0.0f),
    	glm::vec3(0.0f, 1.0f, 0.0f)
	);

	Shader v(GL_VERTEX_SHADER, util::read_file("../shaders/vert.glsl"));
	v.compile();
	Shader f(GL_FRAGMENT_SHADER, util::read_file("../shaders/frag.glsl"));
	f.compile();

	ShaderProgram p(v, f);
	p.bind_frag(0, "outColor");
	p.link();
	p.use();
	
	shape->bind();
	GLint posAttrib = p.get_attrib("position");
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(posAttrib);
	
	p.set_uniform("projection", projection);
	p.set_uniform("view", view);

	while(!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shape->draw();
	    glfwSwapBuffers(window);
	    glfwPollEvents();
	    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    		glfwSetWindowShouldClose(window, GL_TRUE);
	}

    glfwTerminate();
}
