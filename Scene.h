#pragma once
#include <vector>

#include "DrawableObject.h"
#include "Camera.h"
#include "Controls.h"
#include "ModelSkybox.h"
#include "ShaderProgram.h"
#include "Material.h"
#include "Mesh.h"
#include "Texture.h"

using namespace std;
using namespace glm;

class Scene
{
public:
	Scene();
	~Scene();

	void CreateForestScene();
	void CreateForestDarkScene();
	void CreateFourSpheres();
	void CreateFourShaderLightsScene();
	void CreateFourSpheresDirectional();

	void DrawScene(float deltaTime);
	
	void mouseCallback(GLFWwindow* window, double xpos, double ypos);
	void processInput(GLFWwindow* window, float deltaTime);

	void setSelectedObject(int index);


	Camera* getCamera() { return this->camera; }
	Controls* getControls() const { return controls; }

	ShaderProgram* getTreeShaderProgram() { return treeShaderProgram; }
	Material* getTreeMaterial() { return treeMaterial; }
	Mesh* getTreeModel() { return treeModel; }
	Texture* getTreeTexture() { return treeTexture; }

	void addDrawableObject(DrawableObject* drawableObject);
	void changeSkyBoxState();
	DrawableObject* getObjectByID(int id);
	void removeDrawableObject(DrawableObject* object);
private:
	vector<DrawableObject*> drawableObjects;
	
	Camera* camera;
	Controls* controls = nullptr;

	DrawableObject* skybox = nullptr;
	ModelSkybox* skybox_model = nullptr;

	DrawableObject* selectedObject = nullptr;

	ShaderProgram* treeShaderProgram = nullptr;
	Mesh* treeModel = nullptr;
	Material* treeMaterial = nullptr;
	Texture* treeTexture = nullptr;

	void RandomTransform2(DrawableObject* object, int i);
	void RandomTransform(DrawableObject* object, int i);
	void SetSkybox(DrawableObject* model);
};

