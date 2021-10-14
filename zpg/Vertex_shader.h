#pragma once

static const char* vertex_shader =
"#version 330\n"
"layout(location=0) in vec4 vp;"
"layout(location=1) in vec4 vc;"
"uniform mat4 modelMatrix;"
"uniform mat4 viewMatrix;"
"uniform mat4 projectionMatrix;"
"out vec4 my_Colour;"
"void main () {"
"     gl_Position = projectionMatrix * viewMatrix * modelMatrix *  vp;"

"     my_Colour = vc;"
"};";