#version 330
layout(location=0) in vec3 in_Position;
layout(location=1) in vec3 in_Normal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec4 in_colour;

out vec4 ex_colour;
out vec4 ex_worldPosition;
out vec3 ex_worldNormal;

void main(void)
{
ex_worldPosition = modelMatrix * vec4(in_Position,1.0f);
ex_worldNormal = mat3(modelMatrix) * in_Normal; //příště
gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(in_Position,1.0f);
ex_colour = vec4(1.0f, 0.7f, 0.05f, 1.f);
}