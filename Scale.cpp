#include "Scale.h"

Scale::Scale(float scale) : scale(scale, scale, scale) {}

mat4 Scale::getMatrix() {
  /* scale = 5 ->
  | 5 0 0 0 |
  | 0 5 0 0 |
  | 0 0 5 0 |
  | 0 0 0 1 |
  */
    return glm::scale(mat4(1.0f), scale);
}
