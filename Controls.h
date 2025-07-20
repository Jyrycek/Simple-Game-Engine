#pragma once

#include "Camera.h"
#include <GLFW/glfw3.h>

class Controls {
public:
    Controls(Camera* cam);

    void processInput(GLFWwindow* window, float deltaTime);
    void mouseCallback(GLFWwindow* window, double xpos, double ypos);
    void setInitialMousePosition(double xpos, double ypos);

private:
    double lastX = -1.0;
    double lastY = -1.0;

    Camera* camera;
};