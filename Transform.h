#pragma once
#include <glm/glm.hpp>

using namespace glm;

class Transform {
public:
    virtual mat4 getMatrix() = 0;
    virtual ~Transform() = default;

};
