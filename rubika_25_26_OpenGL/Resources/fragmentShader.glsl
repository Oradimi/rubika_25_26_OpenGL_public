#version 330 core

in vec3 vColor;
in vec2 vTexCoord;

out vec4 FragColor;

uniform float time;
uniform sampler2D texture0;
uniform sampler2D texture1;

void main()
{
	vec4 color = vec4(vColor * time, 1.0);
	vec4 colorTexture0 = texture(texture0, vTexCoord);
	vec4 colorTexture1 = texture(texture1, vTexCoord);
	//FragColor = mix(colorTexture0, colorTexture1, 0.5) * color;
	FragColor = mix(colorTexture0, colorTexture1, 0.5);
};