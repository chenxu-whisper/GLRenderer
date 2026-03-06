#version 460 core
in vec3 vColor;
in vec2 vTexCoord;

out vec4 FragColor;

uniform sampler2D uColorTexture;
uniform vec4 uColor;
//uniform float uTime;

void main()
{
    vec2 uv = vTexCoord;
    vec4 color = texture(uColorTexture, uv);

    float ease = 1.0;
//    float ease = sin(uTime) * 0.5 + 0.5;
    FragColor = uColor * color;

//    FragColor = vec4(vec3(0.5) , 1.0);
}