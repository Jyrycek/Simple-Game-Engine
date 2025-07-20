#version 400

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

layout(location = 0) in vec3 in_Position;

out vec3 ex_TexCoords;

uniform bool isStatic;
uniform vec3 staticSkyboxPosition;

void main(void) {
    mat4 viewToUse = viewMatrix;
    vec3 positionToUse = in_Position;

    if (isStatic) {
        viewToUse = mat4(mat3(viewMatrix));
        positionToUse += staticSkyboxPosition;
    }

    float scaleFactor = isStatic ? 60.0 : 2.0;
    gl_Position = projectionMatrix * viewToUse * vec4(positionToUse * scaleFactor, 1.0);
    ex_TexCoords = in_Position;
}
