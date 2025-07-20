#pragma once
#include <vector>

#include "Transform.h"

using namespace std;
using namespace glm;

class TransformComposite : public Transform
{
public:
    void addComponent(Transform* component);
    void addDynamicComponent(Transform* component);
    ~TransformComposite();

    void update(float deltaTime);

    mat4 getMatrix() override;
private:
    vector<Transform*> components;
    vector<Transform*> dynamicComponents;
};
