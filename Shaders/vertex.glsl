#version 330

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec3 in_Normal;
layout(location = 2) in vec2 in_TexCoords;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec4 ex_worldPosition;
out vec3 ex_worldNormal;
out vec2 ex_TexCoords;
out vec3 ex_viewDirection;

void main(void) {
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(in_Position, 1.0);
    ex_worldPosition = modelMatrix * vec4(in_Position, 1.0);
    ex_worldNormal = normalize(mat3(transpose(inverse(modelMatrix))) * in_Normal);
    ex_viewDirection = normalize(vec3(inverse(viewMatrix)[3]) - vec3(ex_worldPosition));
    ex_TexCoords = in_TexCoords;
}
