#version 150 core

uniform vec3 color_mod;

in vec3 Color;

out vec4 out_color;

void main()
{
   out_color = vec4(Color * color_mod, 1.0);
}
