#include "Application.h"

int main(void)
{
	Application* app = new Application();
	app->initialize();

	app->createModelsAndShaders();

	app->run();
}