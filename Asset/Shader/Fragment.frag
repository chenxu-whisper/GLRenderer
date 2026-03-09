#version 460 core
in vec4 vColor;
in vec2 vTexCoord;

out vec4 FragColor;

//uniform float uTime;
uniform sampler2D uColorTexture;
uniform vec4 uColor;

void main()
{
    vec2 uv = vTexCoord;
    vec4 color = texture(uColorTexture, uv);

    FragColor = uColor * color;

//    FragColor = vec4(vec3(0.5) , 1.0);
}