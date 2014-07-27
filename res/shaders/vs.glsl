#version 130
uniform vec4 time;

in vec2 position;
in vec3 color;
in vec2 texcoord;

out vec3 Color;
out vec2 Texcoord;

void main()
{
   Color = color;
   Texcoord = texcoord;

   vec3 p = vec3(position, 0.0);

   gl_Position = vec4(p * vec3(Time), 1.0);
}

