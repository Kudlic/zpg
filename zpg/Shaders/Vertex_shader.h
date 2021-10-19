#pragma once

static const char* vertex_shader =
"#version 330\n"
"layout(location=0) in vec3 vp;"
"layout(location=1) in vec3 vc;"
"uniform mat4 modelMatrix;"
"uniform mat4 viewMatrix;"
"uniform mat4 projectionMatrix;"
"out vec4 my_Colour;"
"void main () {"
"     gl_Position = projectionMatrix * viewMatrix * modelMatrix *  vec4(vp, 1);"
"     my_Colour = vec4(vc, 1);"
"};";