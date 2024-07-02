#version 300 es

layout(location = 0) in vec3 pos;

uniform mat4 wvp;

out vec4 color;

void main()
{
    gl_Position = wvp * vec4(pos, 1.0);
    color = vec4(clamp(pos, 0.0, 1.0), 1.0);
}
