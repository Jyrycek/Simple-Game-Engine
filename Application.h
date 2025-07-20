#pragma once

#include "Window.h"
#include "Scene.h"

using namespace glm;

class Application
{
public:
	Application();
	~Application();

	void initialize();
	void createModelsAndShaders();
	void run();
	void switchScene();

	Scene* getCurrentScene() const { return currentScene; }
	int getCurrentSceneIndex() { return currentSceneIndex; }

	void processMouseClick(double xpos, double ypos);
	void processMouseDeletion(double xpos, double ypos);
private:
	Scene* scenes[6] = { };
	Scene* currentScene;

	int currentSceneIndex = 0;
	float lastFrame = 0.0f;
	mat4 projection;
	
};
