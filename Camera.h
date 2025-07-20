#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "Subject.h"
#include "Observer.h"
#include "ShaderProgram.h"

using namespace std;
using namespace glm;

enum class Movement { FORWARD, BACKWARD, LEFT, RIGHT };

class ShaderProgram;
class Camera : public Subject
{
public:
    Camera(vec3 position, vec3 up, float yaw, float pitch);

    mat4 getViewMatrix();
    vec3 getPosition();
    vec3 getFront();

    void processMouseMovement(float xoffset, float yoffset);
    void processKeyboard(Movement direction, float deltaTime);

private:
    vec3 position;
    vec3 front;
    vec3 up;
    vec3 right;
    vec3 worldUp;

    float yaw;
    float pitch;
    float sensitivity;
    float movementSpeed;
    float fov;

    mat4 viewMatrix;

    void updateCameraVectors();
    void updateViewMatrix();

    void notifyViewMatrixObservers();
};