#pragma once
#include <glm/gtc/matrix_transform.hpp>

#include "Transform.h"

using namespace glm;

class Rotation : public Transform {
public:
    Rotation(float angleX, float angleY, float angleZ);
    mat4 getMatrix() override;

private:
    float rotationX, rotationY, rotationZ;
};
