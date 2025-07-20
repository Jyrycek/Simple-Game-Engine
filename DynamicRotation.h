#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include "Rotation.h"

class DynamicRotation : public Transform {
public:
    DynamicRotation(float speedX, float speedY, float speedZ)
        : rotationSpeedX(speedX), rotationSpeedY(speedY), rotationSpeedZ(speedZ),
        rotation(0.0f, 0.0f, 0.0f) {}

    void update(float deltaTime) {
        rotationX += rotationSpeedX * deltaTime;
        rotationY += rotationSpeedY * deltaTime;
        rotationZ += rotationSpeedZ * deltaTime;

        rotationX = fmod(rotationX, 360.0f);
        rotationY = fmod(rotationY, 360.0f);
        rotationZ = fmod(rotationZ, 360.0f);

        rotation = Rotation(rotationX, rotationY, rotationZ);
    }

    mat4 getMatrix() override {
        return rotation.getMatrix();
    }

private:
    float rotationSpeedX, rotationSpeedY, rotationSpeedZ;
    float rotationX = 0.0f, rotationY = 0.0f, rotationZ = 0.0f;

    Rotation rotation;
};
