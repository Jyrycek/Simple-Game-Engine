#version 400

in vec3 ex_TexCoords;

out vec4 out_Color;

uniform samplerCube skybox;

void main(void) {
    // Vykreslení barvy z cubemap textury
    out_Color = texture(skybox, ex_TexCoords);
} 
