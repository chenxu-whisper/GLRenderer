#version 460 core
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;

out vec2 vTexCoord;
out vec3 vColor;

void main()
{
    vTexCoord = aTexCoord;
    vColor = aColor;

    gl_Position = vec4(aPosition, 1.0);
}