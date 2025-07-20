#pragma once
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>

using namespace std;

class Texture {
public:
    Texture(const string& filePath, float uvRepeat);
    ~Texture();

    void bind();
    void unbind();

    GLuint getTextureID() const { return textureID; }
    float getScale() { return uvRepeat; }

private:
    float uvRepeat;
    GLuint textureID;
};
