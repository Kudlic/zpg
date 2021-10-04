#pragma once

static const char* fragment_shader =
"#version 330\n"
"out vec4 frag_colour;"
"in vec4 my_Colour;"
"void main () {"
"     frag_colour = my_Colour;"
"};";