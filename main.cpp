/*
commit : texture Learnopengl.com exercies

exerciese:
1.[done]
make sure only the happy looks in the other/reverse direction 
by changing the fragment shader. solution: fragment_tex_ex1.glsl

2.[done]
Experiment with the different texture wrapping methods by specifying texture coordinates
in the range 0.0f to 2.0 instead of 0.0f to 1.0f.
See if you can display 4 smiley faces on a single container image clamped at its edge.


3.[done]
Try to display only the center pixel of the texture image on the rectangle
in such a way that the individual pixels are getting visible by changing in the 
texture coordinates.
Try to set the texture filtering method to GL_NEAREST to see the pixels more 
clearly.

4.[in progress]
Use a uniform variable as the mix functions's third parameter to vary the amount
the two textures are visible.
Use the up and down arrow keys to change how much the container or the smiley face
is visible.
soluton:fragment_tex_ex4.glsl by adding a uniform 

at this point, we move key_callback out of the utils.h , because it is using some global vars
*/

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>

// Other includes
#include "OE_shader.h"
#include "utils.h"
#include "myGeometry.h"

const GLuint WIDTH = 640, HEIGHT = 480;
GLfloat mixValue = 0.2f;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int main()
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

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "textured Cube move experiment", nullptr, nullptr);

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);
	glewExperimental = GL_TRUE;

	glewInit();
	glViewport(0, 0, WIDTH, HEIGHT);


	// Build and compile our shader program
	
	/* standard output
	OE_shader oeShader("../texturedCube_move/shaders/vertex_ct.glsl", 
		"../texturedCube_move/shaders/fragment_ct.glsl");
	*/
	/*reverse face by modifying fragment:fragment_tex_ex1.glsl*/

	std::cout << "enterering drawing loop:\n";
	OE_shader oeShader("../texturedCube_move/shaders/vertex_ct.glsl",
		"../texturedCube_move/shaders/fragment_tex_ex4.glsl");


	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sample_cube), sample_cube, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
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
	GLuint texture1;
	glGenTextures(1, &texture0);


	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture0);
	// Set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int image_w, image_h;
	unsigned char* image0 = SOIL_load_image("../texturedCube_move/textures/container.jpg",
		&image_w, &image_h, 0, SOIL_LOAD_RGB);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_w, image_h, 0, GL_RGB, GL_UNSIGNED_BYTE, image0);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image0);
	glBindTexture(GL_TEXTURE_2D, 0);


	glGenTextures(1, &texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	unsigned char* image1 = SOIL_load_image("../texturedCube_move/textures/awesomeface.png",
		&image_w, &image_h, 0, SOIL_LOAD_RGB);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_w, image_h, 0, GL_RGB, GL_UNSIGNED_BYTE, image1);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image1);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	// Game loop

	while (!glfwWindowShouldClose(window))
	{
	
		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Activate shader
		oeShader.use_program();

		//bind Textures using texture units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture0);
		glUniform1i(glGetUniformLocation(oeShader.Program, "ourTexture1"), 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glUniform1i(glGetUniformLocation(oeShader.Program, "ourTexture2"), 1);

		glUniform1f(glGetUniformLocation(oeShader.Program, "mixValue"), mixValue);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}
	// Properly de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	// Change value of uniform with arrow keys (sets amount of textre mix)
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		mixValue += 0.1f;
		if (mixValue >= 1.0f)
			mixValue = 1.0f;
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
	{
		mixValue -= 0.1f;
		if (mixValue <= 0.0f)
			mixValue = 0.0f;
	}
}