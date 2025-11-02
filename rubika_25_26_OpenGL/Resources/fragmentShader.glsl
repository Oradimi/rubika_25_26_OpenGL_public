#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 scalar;
};

in vec3 vPos;
in vec3 vNormal;
in vec3 vColor;
in vec2 vTexCoord;

out vec4 FragColor;

uniform float time;
uniform sampler2D textureDiffuse;
uniform sampler2D textureSpecular;

uniform vec3 viewPos;

uniform Material material;
uniform Light light;

void main()
{
    vec4 color = vec4(vColor, 1.0);
    vec4 colorTextureDiffuse = texture(textureDiffuse, vTexCoord);
    vec4 colorTextureSpecular = texture(textureSpecular, vTexCoord);

    vec3 totalLight = vec3(0.0);

    // POINT LIGHT
    float distanceLightFragment = distance(light.position, vPos);
    float attenuation = 1.0 / (1.0 + 0.09 * distanceLightFragment + 0.032 * distanceLightFragment * distanceLightFragment);
    vec3 nLightPosToPosition_vs = normalize(light.position - vPos);
    vec3 nViewPosToPosition_vs = normalize(viewPos - vPos);
    vec3 nNormal_vs = normalize(vNormal);

    float diffuseTerm = max(dot(nLightPosToPosition_vs, nNormal_vs), 0.0);
    vec3 diffuseColor = material.diffuse * diffuseTerm * light.diffuse * attenuation * light.scalar;

    vec3 reflectionDir = reflect(-nLightPosToPosition_vs, nNormal_vs);  
    float specularTerm = pow(max(dot(nViewPosToPosition_vs, reflectionDir), 0.0), material.shininess * 128.0);
    vec3 specularColor = material.specular * specularTerm * attenuation * light.scalar;
    
    totalLight += colorTextureDiffuse.xyz * diffuseColor + colorTextureSpecular.xyz * specularColor + colorTextureDiffuse.xyz * material.ambient * light.ambient;

    FragColor = vec4(totalLight, 1.0) * color;
};