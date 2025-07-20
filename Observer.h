#pragma once
#include <glm/glm.hpp>

class Observer
{
public:
    virtual void updateViewMatrix(const glm::mat4& viewMatrix) = 0;
};

