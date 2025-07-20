#include "DrawableObject.h"

int DrawableObject::nextID = 1;

DrawableObject::DrawableObject(Camera* _camera, Model* model, ShaderProgram* shaderProgram, Material* material, Texture* texture)
    : shaderProgram(shaderProgram), model(model), material(material), texture(texture)
{
    id = nextID++;
    transform = new TransformComposite();
}

DrawableObject::~DrawableObject() {
    delete transform;
    delete model;
    delete shaderProgram;
    delete material;
    delete texture;
}

void DrawableObject::Draw(float deltaTime) {
    mat4 modelMatrix = transform->getMatrix();
    shaderProgram->use(texture);
    transform->update(deltaTime);
    shaderProgram->setProjectionMatrix();

    shaderProgram->setModelMatrix(modelMatrix);
    if (dynamic_cast<ModelSkybox*>(model)) {
        drawSkybox();
    }
    else {
        drawNormalModel();
    }

    shaderProgram->unbind();
}

void DrawableObject::drawSkybox() {
    shaderProgram->setSkyboxTexture();

    ModelSkybox* skybox = dynamic_cast<ModelSkybox*>(model);
    if (skybox) {
        shaderProgram->setShaderStatic(!skybox->getIsStatic());
    }
    model->draw_model();
}

void DrawableObject::drawNormalModel() {

    if (material) {
        shaderProgram->setMaterial(material);
    }

    if (texture) {
        texture->bind();
    }

    model->draw_model();
    
    if (texture) {
        texture->unbind();
    }
    shaderProgram->unbind();

}

void DrawableObject::scale(float scale) {
    transform->addComponent(new Scale(scale));
}

void DrawableObject::translate(float x, float y, float z) {
    transform->addComponent(new Translation(x, y, z));
}

void DrawableObject::rotate(float angleX, float angleY, float angleZ) {
    transform->addComponent(new Rotation(angleX, angleY, angleZ));
}

void DrawableObject::moveDynamic(float x, float y, float z) {
    transform->addDynamicComponent(new Translation(x, y, z));
}

void DrawableObject::Update(float deltaTime) {
    t += deltaTime * 0.1f;
    if (t > 1.0f) t = 0.0f;

    vec3 newPos = bezierCurve->getPoint(t);
    this->moveDynamic(newPos.x, newPos.y, newPos.z);
}

void DrawableObject::addDynamicRotation(float speedX, float speedY, float speedZ) {
    transform->addDynamicComponent(new DynamicRotation(speedX, speedY, speedZ));
}
