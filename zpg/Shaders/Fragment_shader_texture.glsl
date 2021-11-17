#version 330
in vec4 ex_colour;
in vec2 ex_uv;

uniform sampler2D textureUnitID;

out vec4 out_Color;
void main(void)
{
//Output
out_Color = texture(textureUnitID, ex_uv); 
}
