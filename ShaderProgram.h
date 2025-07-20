#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include <stdlib.h>
#include <stdio.h>

#include "SpotLight.h" 
#include "Observer.h"
#include "Camera.h"
#include "Light.h"
#include "Material.h"
#include "Window.h"

#include "ShaderLoader.h"
#include "Texture.h"

class Light;
class Camera;
class ShaderProgram : public Observer, public ShaderLoader
{
public:
	ShaderProgram(Camera* camera);
	~ShaderProgram();

	void initShader(const char* vertex_shader_str, const char* fragment_shader_str);
	void use(Texture * texture);
	void updateViewMatrix(const glm::mat4& viewMatrix) override;

	void setModelMatrix(mat4& modelMatrix);
	void setProjectionMatrix();
	void setViewMatrix(const mat4& viewMatrix);

	void addLight(Light* light);
	void setLights();

	void setMaterial(Material* material);
	void setSkyboxTexture();
	void setTexture(int textureUnit, float uvRepeat);

	void unbind();

	void setUseTexture(bool use) { useTexture = use; }
	void setShaderStatic(bool isStatic);
private:
	Camera* camera;
	vector<Light*> lights;

	bool useTexture;
};

