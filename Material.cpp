#include "Material.h"

Material::Material(const vec3& ambient, const vec3& diffuse, const vec3& specular, float shininess)
    : ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess) {}

vec3 Material::getAmbient() const {
    return ambient;
}

vec3 Material::getDiffuse() const {
    return diffuse;
}

vec3 Material::getSpecular() const {
    return specular;
}

float Material::getShininess() const {
    return shininess;
}
