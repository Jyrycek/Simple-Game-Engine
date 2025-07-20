#pragma once
#include <glm/gtc/matrix_transform.hpp>

#include "Transform.h"

using namespace glm;

class Translation : public Transform {
public:
    Translation(float x, float y, float z);
    mat4 getMatrix() override;

private:
    vec3 translation;
};
