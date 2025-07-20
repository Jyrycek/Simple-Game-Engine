#version 330

in vec4 ex_worldPosition;
in vec3 ex_worldNormal;
in vec2 ex_TexCoords;

struct Material {
    vec3 ambient;
    vec3 diffuse;
};

uniform Material material;
uniform sampler2D textureSampler;
uniform bool useTexture;

out vec4 out_Color;

void main(void) {
    vec4 texColor = vec4(1.0, 1.0, 1.0, 1.0);

    if (useTexture) {
        texColor = texture(textureSampler, ex_TexCoords);
    }
    vec4 color = vec4(material.ambient + material.diffuse, 1.0) * texColor;

    out_Color = color;
}
