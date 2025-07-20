#pragma once
#include <glm/vec3.hpp>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

class BezierCurve {
public:
    BezierCurve(vector<vec3>& points);
    vec3 getPoint(float t);

private:
    mat4 bez_mat = mat4(
        vec4(-1.0, 3.0, -3.0, 1.0),
        vec4(3.0, -6.0, 3.0, 0.0),
        vec4(-3.0, 3.0, 0.0, 0.0),
        vec4(1.0, 0.0, 0.0, 0.0)
    );
    mat4x3 controlPoints;
};


