#include "Translation.h"

Translation::Translation(float x, float y, float z)
    : translation(x, y, z) {}

mat4 Translation::getMatrix() {
    return translate(mat4(1.0f), translation);
}
