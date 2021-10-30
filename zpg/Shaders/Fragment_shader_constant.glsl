#version 330
out vec4 frag_colour;
in vec4 ex_colour;

void main () {
     frag_colour = ex_colour;
};