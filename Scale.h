#pragma once
#include <glm/gtc/matrix_transform.hpp>

#include "Transform.h"

using namespace glm;

class Scale : public Transform {
public:
    Scale(float scale);
    mat4 getMatrix() override;

private:
    vec3 scale;
};
