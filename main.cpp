#include<iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<SOIL.h>

#include"OE_shader.h"  //shader loader and shader linker
#include"utils.h"      //key_callback
#include"myGeometry.h" //vertices coords, EBO indices.

//draw a single cube
GLFWwindow* window;
const int WIDTH = 640, HEIGHT = 480;

int main(int argc, char* argv[])
{
	std::cout << "textured Cube move experiment\n\n\n\n";
	//init glew, glfw,set the window parameters
	
	std::cout << "glfwInit\n" << std::endl;
	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(WIDTH, HEIGHT, "textured Cube move experiment", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	glewInit();

	int width = 0, height = 0;
	glfwGetFramebufferSize(window, &width, &height);
	glfwSetKeyCallback(window, key_callback);
	glViewport(0, 0, width, height);
	
	

	//OE_shader oeShader("../texturedCube_move/shaders/vertex.glsl",
	//	"../texturedCube_move/shaders/fragment.glsl");

	OE_shader oeShader("../shaders/01.vert", "../shaders/01.frag");
	std::cout << "enterering drawing loop:\n";

	GLuint VAO0;
	GLuint VBO0;
	GLuint EBO0;

	glGenVertexArrays(1, &VAO0);
	glGenBuffers(1, &VBO0);
	glGenBuffers(1, &EBO0);

	glBindVertexArray(VAO0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO0);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_with_texCoord), cube_with_texCoord, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO0);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_index), cube_index, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	
		glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		oeShader.use_program();
		glBindVertexArray(VAO0);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}
	glDeleteVertexArrays(1, &VAO0);
	glDeleteBuffers(1, &VBO0);

	glfwTerminate();
	std::cout << "Program ends here\n";
	
	return 0;
}