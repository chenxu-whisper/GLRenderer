#version 460 core
in vec3 vColor;
in vec2 vTexCoord;

out vec4 FragColor;

uniform sampler2D uColorTexture;
uniform float uTime;

void main()
{
    vec2 uv = vTexCoord;
    vec4 color = texture(uColorTexture, uv);

    float ease = sin(uTime) * 0.5 + 0.5;
    FragColor = vec4(color * ease);

//    FragColor = vec4(vec3(0.5) , 1.0);
}