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
	0.9f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // Top Right
	0.8f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // Bottom Right
	0.1f, -0.6f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,   // Bottom Left
	0.2f, 0.4f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f    // Top Left
};

GLint cube_index[] = {
	0,1,2,
	0,2,3
};
#endif