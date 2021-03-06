#version 460 core

in vec3 position;
in vec3 color;
// in vec2 texcoord;

out vec4 fragcolor;
// out vec2 outtexcoord;

uniform mat4 mvp;
// uniform mat4 projection;
// uniform mat4 modelview;

void
main()
{
    gl_Position = mvp * vec4(position, 1.0);
    fragcolor = vec4(color, 1.0);
    // fragcolor = vec4(1.0, 0.0, 0.0, 1.0);

    // gl_Position = projection * modelview * vec4(position, 1.0);
    // outtexcoord = texcoord;
}