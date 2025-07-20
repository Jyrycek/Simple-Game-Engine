#pragma once
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "Subject.h"
#include "Observer.h"

using namespace glm;

class Application;

class Window  {
public:
    static Window& getInstance(int width = 1000, int height = 650, const char* title = "OPENGL") {
        static Window instance(width, height, title);
        return instance;
    }

    int getWidth();
    int getHeight();

    void create();
    void swapBuffers();
    void pollEvents();
    bool shouldClose();

    GLFWwindow* getWindow();

    static void errorCallback(int error, const char* description);
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void windowFocusCallback(GLFWwindow* window, int focused);
    static void windowIconifyCallback(GLFWwindow* window, int iconified);
    static void windowSizeCallback(GLFWwindow* window, int width, int height);
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

    void updateProjectionMatrix();
    mat4 getProjectionMatrix();

    Window(const Window&) = delete;
    void operator=(const Window&) = delete;
private:
    Window(int width, int height, const char* title);
    ~Window();

    mat4 projectionMatrix;

    int width, height;
    GLFWwindow* window;
};