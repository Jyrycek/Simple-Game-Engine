#pragma once
#include <vector>
#include <string>
#include <iostream>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Model.h"
#include "Texture.h"

using namespace glm;
using namespace std;
using namespace Assimp;

struct Vertex {
	vec3 Position;
	vec3 Normal;
	vec2 TextureCoords;
	vec3 Tangent;
};

class Mesh : public Model
{
public:
	Mesh(const string& filename, float scale);

	void draw_model() override;
	float getScale();
private:
	float scale;
};