#version 460 core
in vec3 vColor;
out vec4 FragColor;
uniform float uTime;

void main()
{
    // 使颜色在0.0到1.0之间循环变化
    float ease = sin(uTime) * 0.5 + 0.5;
    FragColor = vec4(vColor * ease, 1.0);

//    FragColor = vec4(vec3(0.5) , 1.0);
}