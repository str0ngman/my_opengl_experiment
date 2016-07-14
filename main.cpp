#include<iostream>
#include<GL/glew.h> //glew
#include<GLFW/glfw3.h> //glfw
#include<SOIL.h> //lib: load image

#include"OE_shader.h"  //shader loader and shader linker
#include"utils.h"      //key_callback(), etc
#include"myGeometry.h" //vertices coords, EBO indices.

//draw a single cube with textures
GLFWwindow* window;
const int WIDTH = 640, HEIGHT = 480;

int main(int argc, char* argv[])
{
	std::system("cls");
	std::cout << "/********textured Cube move experiment*********/\n\n";
	std::cout << "[draw a cube with texture]\n";
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
	
	
	OE_shader oeShader("../texturedCube_move/shaders/vertex_ct.glsl", 
		"../texturedCube_move/shaders/fragment_ct.glsl");
	std::cout << "enterering drawing loop:\n";

	GLuint VAO0;
	GLuint VBO0;
	GLuint EBO0;
	glGenVertexArrays(1, &VAO0);
	glGenBuffers(1, &VBO0);
	glGenBuffers(1, &EBO0);

	glBindVertexArray(VAO0);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO0);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sample_cube), sample_cube, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO0);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_index), cube_index, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	// Load and create a texture 
	GLuint texture0;
	glGenTextures(1, &texture0);
	glBindTexture(GL_TEXTURE_2D, texture0);
	// Set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	int image_w, image_h;
	//unsigned char* image0 = SOIL_load_image("../texturedCube_move/textures/container.jpg", 
		//&image_w, &image_h, 0, SOIL_LOAD_RGB);

	unsigned char* image0 = SOIL_load_image("../texturedCube_move/textures/container.jpg", 
		&image_w, &image_h, 0, SOIL_LOAD_RGB);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_w, image_h, 0, GL_RGB, GL_UNSIGNED_BYTE, image0);
	glGenerateMipmap(GL_TEXTURE_2D);
	
	SOIL_free_image_data(image0);
	glBindTexture(GL_TEXTURE_2D, 0);
	

	
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindTexture(GL_TEXTURE_2D, texture0);

		oeShader.use_program();
		glBindVertexArray(VAO0);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}
	glDeleteVertexArrays(1, &VAO0);
	glDeleteBuffers(1, &VBO0);
	glDeleteBuffers(1, &EBO0);

	glfwTerminate();
	std::cout << "Program ends here\n";
	
	return 0;
}