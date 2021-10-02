/*const char* fragment_shader =
"#version 330\n"
"in vec4 my_Colour"
"out vec4 frag_colour;"
"void main () {"
"     frag_colour = my_Colour"
"     frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);"
"};";*/

const char* fragment_shader =
"#version 330\n"
"out vec4 frag_colour;"
"in vec4 my_Colour;"
"void main () {"
"     frag_colour = my_Colour;"
"};";