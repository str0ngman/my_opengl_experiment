#ifndef MYGEOMETRY_H
#define MYGEOMETRY_H
#include<GL/glew.h>

//A SIMPLE TRIANGLE
GLfloat triangle[] = {
	-0.8f, -0.5f, 0.0f,
	 0.0f, -0.5f, 0.0f,
	-0.4f,  0.5f, 0.0f
};

GLfloat cube_with_texCoord[] = {
	// Positions          // Colors           // Texture Coords
	0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 2.0f,   // Top Right
	0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 2.0f, 0.0f,   // Bottom Right
	-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,   // Bottom Left
	-1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 2.0f    // Top Left
};

GLfloat sample_cube[] = {
	// Positions          // Colors           // Texture Coords
	0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // Top Right
	0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Bottom Right
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // Bottom Left
	-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // Top Left 
};

GLint cube_index[] = {
	0,1,2,
	0,2,3
};
#endif