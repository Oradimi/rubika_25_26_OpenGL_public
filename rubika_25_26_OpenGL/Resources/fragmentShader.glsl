#version 330 core

in vec3 vColor;

out vec4 FragColor;

uniform float time;

void main()
{
	vec4 color = vec4(vColor.x * time, vColor.y * time, vColor.z * time, 1.0f);
	FragColor = color;
};