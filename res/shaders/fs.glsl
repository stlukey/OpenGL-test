#version 120
uniform vec4 time_mod;

in vec3 Color;

out vec4 out_color;

vec2 rotate(vec2 p)
{
    return vec2(atan(p.y / p.x), 1. / length(p));
}

void main()
{
    vec2 pos = gl_FragCoord.xy / vec2(800, 400) * 2. - 1.;

    pos = rotate(pos);

    vec2 f = floor(pos * 10.0);

    float d = f.x + f.y;
    float time = time_mod.w;

    out_color = vec4(sin(d + time), sin(d + time * 2.), sin(d+ time * 3.), 1.0);
}

