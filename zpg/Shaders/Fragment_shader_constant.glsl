#version 330
out vec4 frag_colour;
in vec4 my_Colour;
void main () {
     frag_colour = my_Colour;
};