#version 330
layout(location=0) in vec3 in_Position;
layout(location=3) in vec2 in_Tex;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec4 in_colour;

out vec4 ex_colour; 
out vec4 ex_worldPosition;
out vec2 ex_uv;

void main(void)
{
ex_worldPosition = modelMatrix * vec4(in_Position,1.0f);
gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(in_Position,1.0f);
ex_colour = in_colour;
ex_uv = in_Tex;
}