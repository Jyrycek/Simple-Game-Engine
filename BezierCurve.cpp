#include "BezierCurve.h"

BezierCurve::BezierCurve(vector<vec3>& points) {
    controlPoints = mat4x3(points[0], points[1], points[2], points[3]);
}

vec3 BezierCurve::getPoint(float t) {
    //B(t) = (1 - t)^3 * P0  +  3 * (1 - t)^2 * t * P1 +  3 * (1 - t) * t^2 * P2 + t^3 * P3
    vec4 parameters = vec4(t * t * t, t * t, t, 1.0f);
    return parameters * bez_mat * transpose(controlPoints);
}