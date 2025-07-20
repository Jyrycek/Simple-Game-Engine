#pragma once
#include <glm/vec3.hpp>

using namespace glm;

class Material {
public:
    Material(const vec3& ambient, const vec3& diffuse, const vec3& specular, float shininess);

    vec3 getAmbient() const;
    vec3 getDiffuse() const;
    vec3 getSpecular() const;
    float getShininess() const;

private:
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
