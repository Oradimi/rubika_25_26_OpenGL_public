#version 330 core

in vec3 vPos;
in vec3 vColor;
in vec2 vTexCoord;
in vec3 vNormal;

out vec4 FragColor;

uniform float time;
uniform sampler2D texture0;
uniform sampler2D texture1;

uniform float ambiantLightIntensity;
uniform vec3 ambiantLightColor;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 lightDir;

uniform vec3 viewPos;

uniform float uShininess;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 
  
uniform Material material;

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 scalar;
}; 
  
uniform Light light;

void main()
{
	//vec4 color = vec4(vColor * time, 1.0);
	//vec4 colorTexture0 = texture(texture0, vTexCoord);
	//vec4 colorTexture1 = texture(texture1, vTexCoord);
	//FragColor = mix(colorTexture0, colorTexture1, 0.5) * color;
	//FragColor = mix(colorTexture0, colorTexture1, 0.5);

	

    // WORLD LIGHT
    //vec3 nLightDir_vs = normalize(lightDir);

	//float diffuseTerm = max(dot(nLightDir_vs, nNormal_vs), 0.0);
    //vec3 diffuseColor = uKd * diffuseTerm;

	//float specularTerm = pow(max(dot(nNormal_vs, halfwayVector), 0.0), uShininess);
    //vec3 specularColor = uKs * specularTerm;

	//totalLight += ambiantLightIntensity * (ambiantLightColor + specularColor);

    vec3 totalLight = vec3(0.0);

    // POINT LIGHT
	float distanceLightFragment = distance(light.position, vPos);
    vec3 nLightPosToPosition_vs = normalize(light.position - vPos);
    vec3 nViewPosToPosition_vs = normalize(viewPos - vPos);
    vec3 nNormal_vs = normalize(vNormal);
    //vec3 nPosition_vs = normalize(-vPos);
        
    //vec3 halfwayVector = normalize(nLightPosToPosition_vs + nPosition_vs);

    float diffuseTerm = max(dot(nLightPosToPosition_vs, nNormal_vs), 0.0);
    vec3 diffuseColor = material.diffuse * diffuseTerm * light.diffuse;

    vec3 reflectionDir = reflect(-nLightPosToPosition_vs, nNormal_vs);  
    float specularTerm = pow(max(dot(nViewPosToPosition_vs, reflectionDir), 0.0), material.shininess * 128.0);
    vec3 specularColor = material.specular * specularTerm * light.scalar;

    float attenuation = 1.0 / (distanceLightFragment * distanceLightFragment);
    
    totalLight += 1.0 * attenuation * (diffuseColor + specularColor + material.ambient * light.ambient);


	FragColor = vec4(totalLight, 1.0);
};