#include<iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<SOIL.h>

#include"OE_shader.h"
#include"utils.h"
#include"myGeometry.h"


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

	OE_shader oeShader("../shaders/01.vert", "../shaders/01.frag");
	
	int width = 0, height = 0;
	glfwGetFramebufferSize(window, &width, &height);
	glfwSetKeyCallback(window, key_callback);
	glViewport(0, 0, width, height);

	std::cout << "enterering drawing loop:\n";
	while (!glfwWindowShouldClose(window))
	{
		
		glfwPollEvents();
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	std::cout << "Program ends here\n";
	
	return 0;
}