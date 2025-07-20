#pragma once
#include <GL/glew.h>

#include <string.h> 
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


using namespace std;

class ShaderLoader
{
	GLuint vertexID = 0;
	GLuint fragmentID = 0;
	string loadFile(const char* fname);
protected:
	GLuint	shaderProgramID = 0;
public:
	GLuint loadShader(const char* vertexFile, const char* fragmentFile);
	void deleteShader();
	ShaderLoader();
	ShaderLoader(const char* vertexFile, const char* fragmentFile, GLuint* shaderID);
	~ShaderLoader();
};
