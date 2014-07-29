#version 130
uniform vec4 time;

uniform mat4x4 model;
uniform mat4x4 view;
uniform mat4x4 proj;

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

   gl_Position = proj * view * model * vec4(p * vec3(time), 1.0);
}

