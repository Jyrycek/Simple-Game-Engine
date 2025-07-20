#include "Application.h"

Application::Application() {
	Window& window = Window::getInstance(1000, 650, "OPENGL");

	scenes[0] = new Scene();
	scenes[1] = new Scene();
	scenes[2] = new Scene();
	scenes[3] = new Scene();
	scenes[4] = new Scene();
	currentScene = scenes[0];
}

Application::~Application() {
	delete currentScene;
}

void Application::initialize() {
	Window& window = Window::getInstance();
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		cerr << "Failed to initialize GLEW" << endl;
		return;
	}

	glfwSetWindowUserPointer(window.getWindow(), this);
	glfwSetCursorPosCallback(window.getWindow(), [](GLFWwindow* window, double xpos, double ypos) {
    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (app && app->currentScene && glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {
        app->currentScene->mouseCallback(window, xpos, ypos);
    }
});
}

void Application::createModelsAndShaders()
{
	scenes[0]->CreateForestScene();
	scenes[1]->CreateForestDarkScene();
	scenes[2]->CreateFourSpheres();
	scenes[3]->CreateFourShaderLightsScene();
	scenes[4]->CreateFourSpheresDirectional();
}

void Application::run()
{
	float deltaTime = 0.0f;
	Window& window = Window::getInstance();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	while (!window.shouldClose()) {
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		if (currentScene)
		{
			currentScene->processInput(window.getWindow(), deltaTime);
			currentScene->DrawScene(deltaTime);
		}
		window.pollEvents();
		window.swapBuffers();
	}
}

void Application::switchScene() {
	  currentSceneIndex = (currentSceneIndex + 1) % 5;
	  currentScene = scenes[currentSceneIndex];
}

void Application::processMouseClick(double xpos, double ypos) {
	Window& window = Window::getInstance();

	GLint windowWidth = window.getWidth();
	GLint windowHeight = window.getHeight();

	GLint adjustedY = windowHeight - static_cast<GLint>(ypos);

	GLbyte color[4];
	GLfloat depth;
	GLuint index;

	glReadPixels(static_cast<GLint>(xpos), adjustedY, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
	glReadPixels(static_cast<GLint>(xpos), adjustedY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);

	vec3 screenPos = vec3(xpos, adjustedY, depth);
	mat4 viewMatrix = currentScene->getCamera()->getViewMatrix();
	mat4 projectionMatrix = window.getProjectionMatrix();
	vec4 viewport = vec4(0, 0, windowWidth, windowHeight);
	vec3 worldPos = unProject(screenPos, viewMatrix, projectionMatrix, viewport);

	//printf("World position: [%f, %f, %f]\n", worldPos.x, worldPos.y, worldPos.z);

	ShaderProgram* shaderProgram = currentScene->getTreeShaderProgram();
	Material* treeMaterial = currentScene->getTreeMaterial();
	Mesh* treeModel = currentScene->getTreeModel();
	Texture* treeTexture = currentScene->getTreeTexture();

	DrawableObject* tree = new DrawableObject(currentScene->getCamera(), treeModel, shaderProgram, treeMaterial, treeTexture);
	tree->translate(worldPos.x, worldPos.y, worldPos.z);
	tree->scale(0.05);
	currentScene->addDrawableObject(tree);
}

void Application::processMouseDeletion(double xpos, double ypos) {
	Window& window = Window::getInstance();

	GLint windowWidth = window.getWidth();
	GLint windowHeight = window.getHeight();
	GLint adjustedY = windowHeight - static_cast<GLint>(ypos);

	GLint objectID = -1;
	glReadPixels(static_cast<GLint>(xpos), adjustedY, 1, 1, GL_STENCIL_INDEX, GL_INT, &objectID);
	printf("Id podle st. bufferu: %d \n", objectID);


	DrawableObject* selectedObject = currentScene->getObjectByID(objectID);

	if (selectedObject != nullptr) {
		currentScene->removeDrawableObject(selectedObject);
	}
}
