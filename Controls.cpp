#include "Controls.h"

Controls::Controls(Camera* cam) : camera(cam) {}

void Controls::processInput(GLFWwindow* window, float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->processKeyboard(Movement::FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->processKeyboard(Movement::BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->processKeyboard(Movement::LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->processKeyboard(Movement::RIGHT, deltaTime);
}


void Controls::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    if (lastX == -1.0 && lastY == -1.0) {
        lastX = xpos;
        lastY = ypos;
    }

    float xOffset = xpos - lastX;
    float yOffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera->processMouseMovement(xOffset, yOffset);
}

void Controls::setInitialMousePosition(double xpos, double ypos) {
    this->lastX = xpos;
    this->lastY = ypos;
}
