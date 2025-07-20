#version 400
#define MAX_LIGHTS 4

in vec4 ex_worldPosition;
in vec3 ex_worldNormal;
in vec3 ex_viewDirection;
in vec2 ex_TexCoords;

struct Light {
    vec3 position;
    vec3 direction;
    vec3 lightColor;
    float lightIntensity;
    float constantAttenuation;
    float linearAttenuation;
    float quadraticAttenuation; 
    float cutAngle;
    // 0: POINT, 1: DIRECTIONAL, 2: SPOT
    int type;
};

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform Light lights[MAX_LIGHTS];
uniform Material material;
uniform int numberOfLights;
uniform sampler2D textureSampler;
uniform int useTexture;

uniform float uvRepeat;

out vec4 out_Color;

void main(void) {
    vec3 normal = normalize(ex_worldNormal);
    vec2 repeatedTexCoords = ex_TexCoords * uvRepeat;
    vec4 totalDiffuse = vec4(0.0);
    vec4 result = vec4(material.ambient, 1.0);

    for (int i = 0; i < numberOfLights; ++i) {
        float distance = length(lights[i].position - vec3(ex_worldPosition));
        vec3 lightDirection = vec3(0.0);
        float attenuation = 1.0;

        if (lights[i].type == 0) {
            attenuation = 1.0 / (lights[i].constantAttenuation + lights[i].linearAttenuation * distance + lights[i].quadraticAttenuation * distance * distance);
            lightDirection = normalize(lights[i].position - vec3(ex_worldPosition));
        }
        else if (lights[i].type == 1) {
            lightDirection = normalize(-lights[i].direction); 
        }
        else if (lights[i].type == 2) {
            attenuation = 1.0 / (lights[i].constantAttenuation + lights[i].linearAttenuation * distance + lights[i].quadraticAttenuation * distance * distance);
            lightDirection = normalize(lights[i].position - vec3(ex_worldPosition));
            float theta = dot(lightDirection, normalize(-lights[i].direction));
            float epsilon = lights[i].cutAngle - 0.02;
            float intensity = clamp((theta - epsilon) / (lights[i].cutAngle - epsilon), 0.0, 1.0);
            attenuation *= intensity;
        }
        float diff = max(dot(normal, lightDirection), 0.0);
        vec4 totalDiffuse = diff * vec4(lights[i].lightColor, 1.0) * lights[i].lightIntensity * vec4(material.diffuse, 1.0);
        vec3 halfwayVec = normalize(ex_viewDirection + lightDirection);
        float spec = pow(max(dot(normal, halfwayVec), 0.0), material.shininess);
        vec4 specular = vec4(lights[i].lightColor, 1.0) * spec * lights[i].lightIntensity * vec4(material.specular, 1.0);
        result += (totalDiffuse + specular) * attenuation;
    }
    vec4 texColor = texture(textureSampler, repeatedTexCoords);

    if (useTexture == 1) {
        out_Color = result * texColor;
    } else {
        out_Color = result;
    }
}
