#include "Rotation.h"

Rotation::Rotation(float angleX, float angleY, float angleZ)
    : rotationX(angleX), rotationY(angleY), rotationZ(angleZ) {}

mat4 Rotation::getMatrix() {
    /* rotationX = 30
    | 1    0        0    0 |
    | 0 cos(30) -sin(30) 0 |
    | 0 sin(30) cos(30)  0 |
    | 0    0      0      1 |
    */
    mat4 rotX = rotate(mat4(1.0f), radians(rotationX), vec3(1, 0, 0));
    /* rotationY = 30
    | cos(30)   0 sin(30)  0 |
    |   0       1    0     0 |
    | -sin(30)  0 cos(30)  0 |
    |    0      0    0     1 |
    */
    mat4 rotY = rotate(mat4(1.0f), radians(rotationY), vec3(0, 1, 0));
    /* rotationZ = 30
    | cos(30)    -sin(30)   0 0 |
    | sin(30)     cos(30)   0 0 |
    |    0          0       1 0 |
    |    0          0       0 1 |
    */
    mat4 rotZ = rotate(mat4(1.0f), radians(rotationZ), vec3(0, 0, 1));

    return rotZ * rotY * rotX;
}
