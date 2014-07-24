#version 120
uniform vec4 time_mod;

in vec2 position;
in vec3 color;

out vec3 Color;

void main()
{
   Color = color;
   vec3 p = vec3(position, 0.0);

   gl_Position = vec4(p * vec3(time_mod), 1.0);
}

