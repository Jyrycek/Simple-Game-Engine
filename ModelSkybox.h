#pragma once
#include "Model.h"
#include <vector>
#include <string>

using namespace std;

class ModelSkybox : public Model
{
public:
    ModelSkybox(const vector<string>& texturePaths);
    ~ModelSkybox();

    void draw_model() override;

    void setStatic(bool isStatic);
    bool getIsStatic() { return isStatic; }
private:
    GLuint loadSkyboxTextures(const vector<string>& texturePaths);
    void init_model_skybox(const vector<float>& vertices);

    GLuint skyboxTexture;
    bool isStatic = false;
};
