#version 150 core

uniform vec3 time_mod;

in vec3 Color;

out vec4 out_color;

void main()
{
    out_color = vec4(Color * time_mod, 1.0);
}

