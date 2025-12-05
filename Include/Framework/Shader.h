#ifndef GLRENDERER_SHADER_H
#define GLRENDERER_SHADER_H

#include "Core.h"

class Shader
{
public:
    Shader();
    ~Shader();

    /* 加载、编译并链接顶点着色器和片段着色器
     * @param vertexShaderPath: 顶点着色器文件路径
     * @param fragmentShaderPath: 片段着色器文件路径
     */
    void LoadCompileShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

    // glUseProgram: 绑定着色器程序
    void UseShaderProgram() const;
    void EndShaderProgram() const;

    /* 设置浮点数类型的uniform变量值
     * @param name: uniform变量的名称，用于在着色器中定位该变量
     * @param value: 要设置的浮点数值
     */
    void SetFloatUniform(const std::string& name, float value) const;
    // 暂时没有glm库
    // void SetVec3Uniform(const std::string& name, const glm::vec3& value) const;

private:
    /* 检查着色器编译或链接错误
     * @param target: 要检查的着色器目标（顶点着色器或片段着色器）
     * @param targetType: 目标类型字符串（"COMPILE"或"LINK"）
     */
    void CheckShaderError(GLuint target, const std::string &targetType);

private:
    GLuint mShaderProgram{};
};


#endif //GLRENDERER_SHADER_H