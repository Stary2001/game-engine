#define _USE_MATH_DEFINES
#include <math.h>

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
#include "gl/texture.h"
#include "obj.h"

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

	glEnable(GL_DEPTH_TEST);

	Model::ptr shape = OBJ::load("../cube.obj");

	GLfloat screen_width = 800.0f;
	GLfloat screen_height = 600.0f;

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), screen_width / screen_height, 0.1f, 100.0f);

	//glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -2.0f));
	glm::mat4 model;

	glm::mat4 view = glm::lookAt(
    	glm::vec3(4.0f, 3.0f, 3.0f),
    	glm::vec3(0.0f, 0.0f, 0.0f),
    	glm::vec3(0.0f, 1.0f, 0.0f)
	);

	Shader v(GL_VERTEX_SHADER, util::read_file("../shaders/vert.glsl"));
	v.compile();
	Shader f(GL_FRAGMENT_SHADER, util::read_file("../shaders/frag.glsl"));
	f.compile();

	ShaderProgram p(v, f);
	p.bind_frag(0, "outColor");
	p.bind_frag(1, "texcoord");
	p.link();
	p.use();
	
	shape->bind();
	
	GLint posAttrib = p.get_attrib("position");
	GLint normalAttrib = p.get_attrib("normal");
	GLint texAttrib = p.get_attrib("texcoord");

	glEnableVertexAttribArray(posAttrib);
	glEnableVertexAttribArray(normalAttrib);
	glEnableVertexAttribArray(texAttrib);

	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, (8*sizeof(GLfloat)), 0);
	glVertexAttribPointer(normalAttrib, 3, GL_FLOAT, GL_FALSE, (8*sizeof(GLfloat)), (void*)(3 * sizeof(GLfloat)));
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, (8*sizeof(GLfloat)), (void*)(6 * sizeof(GLfloat)));

	Texture::ptr t = std::make_shared<Texture>("../checkers.png");

	p.set_uniform("projection", projection);
	p.set_uniform("view", view);
	p.set_uniform("model", model);
	//p.set_uniform("tex", t);

	while(!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shape->draw();
	    glfwSwapBuffers(window);
	    glfwPollEvents();

	    model = glm::rotate(model, (float)(M_PI / 100.0f), Vec3D(0.0f, 1.0f, 0.0f));
	    p.set_uniform("model", model);

	    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    		glfwSetWindowShouldClose(window, GL_TRUE);
	}

    glfwTerminate();
}
