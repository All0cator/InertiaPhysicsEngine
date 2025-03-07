#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;

out VS_OUT
{
	vec3 fragNormal;
	vec3 fragPos;
	vec4 fragPosLightSpace;
} vs_out;

uniform mat4 model;
uniform mat4 vp;
uniform mat4 lightMatrix;
uniform mat3 normalMatrix; // in world space transpose(inverse(mat3(model)));

uniform float reverseNormals; // for example when rendering inside cube set it to -1.0f if outside of geometry

void main()
{
	vs_out.fragNormal = normalMatrix * (normal * -reverseNormals);
	vs_out.fragPos = vec3(model * vec4(pos, 1.0f));
	vs_out.fragPosLightSpace = lightMatrix * vec4(vs_out.fragPos, 1.0f);
	gl_Position = vp * vec4(vs_out.fragPos, 1.0f);
}