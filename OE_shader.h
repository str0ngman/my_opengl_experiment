//OpenGL Experiment Shader(OE_SHADER) header file
#ifndef SHADER_H
#define SHADER_H
#include<GL/glew.h>

class OE_shader{
public:
	OE_shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	void use_program();

public:
	GLuint Program;
};

#endif //SHADER_H
