#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "ShaderProgram.h"
#include "Model.h"
#include "TransformComposite.h"
#include "Rotation.h"
#include "Scale.h"
#include "Translation.h"
#include "Material.h"

#include "Models/sphere.h"
#include "Models/tree.h"
#include "Models/bushes.h"
#include "Models/gift.h"
#include "Models/plain.h"
#include "Models/suzi_flat.h"
#include "Models/suzi_smooth.h"

#include "ModelSkybox.h"
#include "Texture.h"
#include "BezierCurve.h"
#include "DynamicRotation.h"

using namespace glm;

class DrawableObject {
public:
    DrawableObject(Camera* _camera, Model* model, ShaderProgram* shaderProgram, Material* material, Texture* texture);
    ~DrawableObject();

    void Draw(float deltaTime);

    void scale(float scale);
    void translate(float x, float y, float z);
    void rotate(float angleX, float angleY, float angleZ);

    void drawSkybox();
    void drawNormalModel();

    void addBezier(BezierCurve* bezierCurve) { this->bezierCurve = bezierCurve;}
    BezierCurve* getBezierCurve() { return this->bezierCurve;}
    int getID() const { return id; }

    void Update(float deltaTime);
    void moveDynamic(float x, float y, float z);
    void addDynamicRotation(float speedX, float speedY, float speedZ);

private:
    ShaderProgram* shaderProgram;
    Model* model;
    TransformComposite* transform;
    Material* material;
    Texture* texture;

    BezierCurve* bezierCurve;
    float t;
    int id;
    static int nextID;
};
