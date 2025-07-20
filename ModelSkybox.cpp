#include "ModelSkybox.h"
#include <iostream>

ModelSkybox::ModelSkybox(const vector<string>& texturePaths)
    : Model({}, false)
{
    const float skycube[108] = {
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
    };


    vector<float> vertices(skycube, skycube + sizeof(skycube) / sizeof(skycube[0]));
    vertexCount = vertices.size() / 3;
    init_model_skybox(vertices);

    skyboxTexture = loadSkyboxTextures(texturePaths);
}

ModelSkybox::~ModelSkybox()
{
    glDeleteTextures(1, &skyboxTexture);
}

GLuint ModelSkybox::loadSkyboxTextures(const vector<string>& texturePaths)
{
    if (texturePaths.size() != 6) {
        cerr << "Skybox requires 6 texture paths" << endl;
        return 0;
    }

    GLuint textureID = SOIL_load_OGL_cubemap(
        texturePaths[0].c_str(), texturePaths[1].c_str(),
        texturePaths[2].c_str(), texturePaths[3].c_str(),
        texturePaths[4].c_str(), texturePaths[5].c_str(),
        SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS
    );

    if (textureID == 0) {
        cerr << "Failed to load cubemap textures: " << SOIL_last_result() << endl;
    }

    return textureID;
}

void ModelSkybox::draw_model()
{
    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);

    glDepthFunc(GL_LEQUAL);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    glDepthFunc(GL_LESS);
}

void ModelSkybox::init_model_skybox(const vector<float>& vertices)
{
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}

void ModelSkybox::setStatic(bool isStatic) {
    this->isStatic = isStatic;
}