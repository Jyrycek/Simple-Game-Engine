#include "TransformComposite.h"
#include "Translation.h"
#include "DynamicRotation.h"

TransformComposite::~TransformComposite() {
    for (auto* component : components) {
        delete component;
    }
    for (auto* dynamicComponent : dynamicComponents) {
        delete dynamicComponent;
    }
}

mat4 TransformComposite::getMatrix() {
    mat4 result = mat4(1.0f);
    for (auto* component : components) {
        result *= component->getMatrix();
    }

    for (auto* dynamicComponent : dynamicComponents) {
        result *= dynamicComponent->getMatrix();
    }
    return result;
}

void TransformComposite::addComponent(Transform* component) {
    components.push_back(component);
}

void TransformComposite::addDynamicComponent(Transform* component) {
    dynamicComponents.clear();
    dynamicComponents.push_back(component);
}

void TransformComposite::update(float deltaTime) {
    for (auto* dynamicComponent : dynamicComponents) {
        if (auto* dynamicRotation = dynamic_cast<DynamicRotation*>(dynamicComponent)) {
            dynamicRotation->update(deltaTime);
        }
    }
}
