#include "Light.h"

vec3 Light::getPosition() {
	return position;
}

vec3 Light::getColor() {
	return color;
}

float Light::getIntensity() {
    return intensity; 
}

void Light::setPosition(const vec3& position) {
    this->position = position;
}

void Light::setAttenuation(float constantAttenuation, float linearAttenuation, float quadraticAttenuation) {
    this->constantAttenuation = constantAttenuation;
    this->linearAttenuation = linearAttenuation;
    this->quadraticAttenuation = quadraticAttenuation;
}