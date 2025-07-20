#pragma once
#include "Light.h"

class SpotLight : public Light {
public:
    SpotLight(const vec3& position, const vec3& color)
        : Light(position, color) {
        this->setType(SPOT);
    }

    void setDirection(const vec3& direction) {
        this->direction = direction;
    }

    vec3 getDirection() const {
        return direction;
    }

    void setAngle(float angle) {
        this->angle = cos(radians(angle));
    }

    float getAngle() const {
        return angle;
    }

private:
    vec3 direction;
    float angle;
};
