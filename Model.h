#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <SOIL.h>
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace std;

class Model
{
public:
	Model(const vector<float>& vertices, bool hasTexture);
	~Model();
	virtual void draw_model();

private:
	GLenum drawMode = GL_TRIANGLES;
protected:
	GLuint VAO, VBO, IBO;
	GLsizei vertexCount;

	virtual void init_model(const vector<float>& vertices, bool hasTexture);
};