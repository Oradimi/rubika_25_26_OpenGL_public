#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec3 aColor;
layout(location = 3) in vec2 aTexCoord;

out vec3 vPos;
out vec3 vColor;
out vec2 vTexCoord;
out vec3 vNormal;

uniform mat4 uMVPMatrix;
uniform mat4 uModelMatrix;

void main()
{
    gl_Position = uMVPMatrix * vec4(aPos, 1.0);
    vPos = (uModelMatrix * vec4(aPos, 1.0)).xyz;
    vColor = aColor;
    vTexCoord = aTexCoord;
    vNormal = normalize(transpose(inverse(uModelMatrix)) * vec4(aNormal, 1.0)).xyz;
};