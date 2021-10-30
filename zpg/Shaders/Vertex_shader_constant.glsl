#version 330
layout(location=0) in vec3 vp;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec4 in_colour;

out vec4 ex_colour;

void main () {
     gl_Position = projectionMatrix * viewMatrix * modelMatrix *  vec4(vp, 1);
     ex_colour = in_colour;
};