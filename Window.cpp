#include "Window.h"
#include "Application.h"

Window::Window(int width, int height, const char* title) : width(width), height(height), window(nullptr) {
    glfwSetErrorCallback(errorCallback);
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW\n");
        exit(EXIT_FAILURE);
    }
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    create();
    updateProjectionMatrix();
}

Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::create() {
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glfwSetKeyCallback(window, keyCallback);
    glfwSetWindowFocusCallback(window, windowFocusCallback);
    glfwSetWindowIconifyCallback(window, windowIconifyCallback);
    glfwSetWindowSizeCallback(window, windowSizeCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
}

void Window::swapBuffers() {
    glfwSwapBuffers(window);
}

void Window::pollEvents() {
    glfwPollEvents();
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(window);
}

void Window::errorCallback(int error, const char* description) {
    fputs(description, stderr);
}

GLFWwindow* Window::getWindow() {
    return window;
}

void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        app->switchScene();
    }

    if (key == GLFW_KEY_F && action == GLFW_PRESS) {
        if (app->getCurrentScene())
        {
            app->getCurrentScene()->changeSkyBoxState();
        }
    }

    if (key == GLFW_KEY_G && action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        app->processMouseDeletion(xpos, ypos);
    }

}

void Window::windowFocusCallback(GLFWwindow* window, int focused) {}

int Window::getWidth() {
    return width;
}

int Window::getHeight() {
    return height;
}

void Window::windowIconifyCallback(GLFWwindow* window, int iconified) {}

void Window::windowSizeCallback(GLFWwindow* window, int width, int height) {
    Window& win = getInstance();
    win.width = width;
    win.height = height;
    win.updateProjectionMatrix();

}
void Window::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (!app) return;
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        if (action == GLFW_PRESS) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);

            if (app && app->getCurrentScene()) {
                app->getCurrentScene()->getControls()->setInitialMousePosition(xpos, ypos);
            }
        }
        else if (action == GLFW_RELEASE) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);
            if (app->getCurrentSceneIndex() == 0)
            {
                app->processMouseClick(xpos, ypos);
            }
        }
    }
}

void Window::updateProjectionMatrix() {

    if (height == 0) { height = 1; }
    float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
    float fov = glm::radians(35.0f);

    float nearPlane = 0.1f;
    float farPlane = 100.0f;

    projectionMatrix = perspective(fov, aspectRatio, nearPlane, farPlane);
    glViewport(0, 0, width, height);
}

mat4 Window::getProjectionMatrix() {
    return projectionMatrix;
}