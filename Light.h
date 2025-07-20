#pragma once
#include <glm/glm.hpp>

using namespace glm;

enum LightType { POINT, DIRECTIONAL, SPOT };

class Light {
public:
    Light(const vec3& position, const vec3& color)
        : position(position), color(color) {}

    void setPosition(const vec3& position);
    vec3 getPosition();

    vec3 getColor();

    float getIntensity();

    void setAngle(float angle) { this->angle = cos(radians(angle)); }
    float getAngle() { return angle; }

    float getConstantAttenuation() const { return constantAttenuation; }
    float getLinearAttenuation() const { return linearAttenuation; }
    float getQuadraticAttenuation() const { return quadraticAttenuation; }

    void setDirection(vec3& direction) { this->direction = direction; }
    vec3 getDirection() { return direction; }

    LightType getType() { return type; }
    void setType(LightType type) { this->type = type; }
    vec4 getAmbient() const { return ambient; }
    void setAttenuation(float constantAttenuation, float linearAttenuation, float quadraticAttenuation);
    void setIntensity(float newIntensity) { this->intensity = newIntensity; }
    virtual ~Light() {}

private:
    vec3 position;
    vec3 color;
    vec4 ambient = vec4(0.05, 0.05, 0.05, 1.0);
    float intensity = 1.0f;
    LightType type = POINT;

    float constantAttenuation = 0.5f;
    float linearAttenuation = 0.2f;
    float quadraticAttenuation = 0.05f;

    float angle = cos(radians(5.0f));

    vec3 direction = vec3(0.0f, -1.0f, 0.0f);
};
