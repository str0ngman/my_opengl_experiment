#include<iostream>
#include<fstream>
#include<string>

#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include"OE_shader.h"


/*constructor of OE_shader:
1. read file data to source
2. compile shaders
3. check compile errors
4. create, attach and link program
5. check program errors
6. delete vertex, fragment shaders

*/
OE_shader::OE_shader(const GLchar* path1,
	const GLchar* path2)
{
	//1. read file data to source
	using namespace std;
	ifstream vertexIn(path1);
	ifstream fragmentIn(path2);
	string vstring((istreambuf_iterator<char>(vertexIn)),
		istreambuf_iterator<char>());
	string fstring((istreambuf_iterator<char>(fragmentIn)),
		istreambuf_iterator<char>());
	const char* vertexSource = vstring.c_str();
	const char* fragmentSource = fstring.c_str();
	cout << "------vertexSource----------------\n" <<vertexSource<< endl;
	cout << "------fragmentSource----------------\n" << fragmentSource << "\n--------------------------------" << endl;


	//2. compile shaders 
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);


	//3. check compile errors
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
			<< "infoLog: " << infoLog << std::endl;
	}
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::fragment::COMPILATION_FAILED\n"
			<< "infoLog: " << infoLog << std::endl;
	}

	//4. create , attach, link program
	this->Program = glCreateProgram();
	glAttachShader(this->Program, vertexShader);
	glAttachShader(this->Program, fragmentShader);
	glLinkProgram(this->Program);


	//5. check program error
	glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
			<< "infoLog" << infoLog << std::endl;
	}

	//6. delete shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}
void OE_shader::use_program(){
	glUseProgram(this->Program);
}

