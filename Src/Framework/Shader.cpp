#include "Shader.h"

Shader::Shader() = default;

Shader::~Shader() = default;

void Shader::LoadCompileShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
    // 读取文件内容到字符串
    std::string vertexCode;
    std::string fragmentCode;

    // 打开文件流并读取内容到字符串流
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // 设置文件流异常标志
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    // 尝试读取文件流内容到字符串流
    try
    {
        // 打开文件流
        vShaderFile.open(vertexShaderPath);
        fShaderFile.open(fragmentShaderPath);

        if (!vShaderFile.is_open() || !fShaderFile.is_open())
        {
            std::cerr << "ERROR::SHADER::FILE_NOT_FOUND - Paths: " << vertexShaderPath << ", " << fragmentShaderPath << std::endl;
            return;
        }

        // 读取文件流内容到字符串流
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        // 关闭文件流
        vShaderFile.close();
        fShaderFile.close();

        // 提取字符串流内容到字符串
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e) //
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESS" << e.what() <<std::endl;
    }

    // 转换字符串为C字符串指针
    const GLchar* vertexShaderSource = vertexCode.c_str();
    const GLchar* fragmentShaderSource = fragmentCode.c_str();

    // 创建顶点/片段着色器对象，返回编号（句柄）
    GLuint vertexShader = 0;
    GLuint fragmentShader = 0;

    /*
     * @brief 创建顶点/片段着色器对象，返回编号（句柄）
     * @param type: 要创建的着色器类型（GL_VERTEX_SHADER或GL_FRAGMENT_SHADER）
     * @return GLuint: 创建的着色器对象句柄
     */
    CHECK_GL_ERROR(vertexShader = glCreateShader(GL_VERTEX_SHADER));
    CHECK_GL_ERROR(fragmentShader = glCreateShader(GL_FRAGMENT_SHADER));

    /*
     * @brief 设置顶点/片段着色器源码
     * @param shader: 要设置源码的着色器对象句柄
     * @param count: 源码字符串数组的元素数量（这里为1）
     * @param strings: 源码字符串数组指针
     * @param lengths: 源码字符串数组每个元素的长度指针（这里为nullptr）
     */
    CHECK_GL_ERROR(glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr));
    CHECK_GL_ERROR(glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr));
    /*
     * @brief 编译顶点/片段着色器对象
     * @param shader: 要编译的着色器对象句柄
     */
    CHECK_GL_ERROR(glCompileShader(vertexShader));
    CHECK_GL_ERROR(glCompileShader(fragmentShader));

    /*
     * @brief 检查顶点/片段着色器编译是否成功
     * @param shader: 要检查的着色器对象句柄
     * @param targetType: 目标类型字符串（"COMPILE"）
     */
    CheckShaderError(vertexShader, "COMPILE");
    CheckShaderError(fragmentShader, "COMPILE");

    /*
     * @brief 创建着色器程序对象，返回编号（句柄）
     * @return GLuint: 创建的着色器程序对象句柄
     */
    CHECK_GL_ERROR(mShaderProgram = glCreateProgram());
    /*
     * @brief 绑定顶点着色器和片段着色器到着色器程序对象
     * @param program: 要绑定着色器的着色器程序对象句柄
     * @param shader: 要绑定的着色器对象句柄
     */
    CHECK_GL_ERROR(glAttachShader(mShaderProgram, vertexShader));
    CHECK_GL_ERROR(glAttachShader(mShaderProgram, fragmentShader));
    /*
     * @brief 链接着色器程序对象
     */
    CHECK_GL_ERROR(glLinkProgram(mShaderProgram));
    /*
     * @brief 检查着色器程序链接是否成功
     * @param program: 要检查的着色器程序对象句柄
     * @param targetType: 目标类型字符串（"LINK"）
     */
    CheckShaderError(mShaderProgram, "LINK");

    /*
     * @brief 删除顶点/片段着色器对象
     * @param shader: 要删除的着色器对象句柄
     */
    CHECK_GL_ERROR(glDeleteShader(vertexShader));
    CHECK_GL_ERROR(glDeleteShader(fragmentShader));
}

void Shader::UseShaderProgram() const
{
    /* 绑定着色器程序，将指定的着色器程序绑定到当前OpenGL状态机，后续的绘制操作将使用该程序的着色器代码
     * @param program: 要绑定的着色器程序ID，这里是shaderProgram
     */
    CHECK_GL_ERROR(glUseProgram(mShaderProgram));
}

void Shader::EndShaderProgram() const
{
    /*
     * @brief 解绑着色器程序，将当前OpenGL状态机的着色器程序ID设置为0，后续的绘制操作将不使用任何着色器
     */
    CHECK_GL_ERROR(glUseProgram(0));
}

void Shader::SetFloatUniform(const std::string &name, float value) const
{
    /*
     * @brief 设置浮点数类型的uniform变量值
     * @param program: 要设置uniform变量值着色器程序对象句柄
     * @param name: uniform变量的名称字符串
     * @param value: 要设置的uniform变量值
     */
    GLint location = glGetUniformLocation(mShaderProgram, name.c_str());
    if (location == -1)
    {
        std::cerr << "ERROR::SHADER::UNIFORM::NOT_FOUND - Name: " << name << std::endl;
        return;
    }
    /*
     * @brief 设置浮点数类型的uniform变量值
     * @param location: uniform变量在着色器程序中的位置索引
     * @param value: 要设置的uniform变量值
     */
    CHECK_GL_ERROR(glUniform1f(location, value));
}

void Shader::SetIntUniform(const std::string &name, int value) const
{
    GLint location = glGetUniformLocation(mShaderProgram, name.c_str());
    if (location == -1)
    {
        std::cerr << "ERROR::SHADER::UNIFORM::NOT_FOUND - Name: " << name << std::endl;
        return;
    }
    /*
     * @brief 设置整数类型的uniform变量值
     * @param location: uniform变量在着色器程序中的位置索引
     * @param value: 要设置的uniform变量值
     */
    CHECK_GL_ERROR(glUniform1i(location, value));
}

void Shader::SetVec3Uniform(const std::string &name, const glm::vec3 &value) const
{
    GLint location = glGetUniformLocation(mShaderProgram, name.c_str());
    if (location == -1)
    {
        std::cerr << "ERROR::SHADER::UNIFORM::NOT_FOUND - Name: " << name << std::endl;
        return;
    }
    CHECK_GL_ERROR(glUniform3fv(location, 1, &value[0]));
}

void Shader::SetVec4Uniform(const std::string &name, const glm::vec4 &value) const
{
    GLint location = glGetUniformLocation(mShaderProgram, name.c_str());
    if (location == -1)
    {
        std::cerr << "ERROR::SHADER::UNIFORM::NOT_FOUND - Name: " << name << std::endl;
        return;
    }
    /*
     * @brief 设置4维向量类型的uniform变量值
     * @param location: uniform变量在着色器程序中的位置索引
     * @param count: 要设置的uniform变量数量，这里是1个
     * @param value: 指向向量数据的指针，这里是value的地址
     */
    CHECK_GL_ERROR(glUniform4fv(location, 1, &value[0]));
}

void Shader::SetMat4x4Uniform(const std::string &name, const glm::mat4 &value) const
{
    GLint location = glGetUniformLocation(mShaderProgram, name.c_str());
    if (location == -1)
    {
        std::cerr << "ERROR::SHADER::UNIFORM::NOT_FOUND - Name: " << name << std::endl;
        return;
    }
    /*
     * @param location: uniform变量在着色器程序中的位置索引
     * @param count: 要设置的uniform变量数量，这里是1个
     * @param transpose: 是否转置矩阵，GL_FALSE表示不转置 GLSL默认列主序，所以这里不转置
     * @param value: 指向矩阵数据的指针，这里是value的地址
     */
    CHECK_GL_ERROR(glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]));
}

void Shader::CheckShaderError(GLuint target, const std::string& targetType)
{
    GLint success;
    GLchar infoLog[512];

    if (targetType == "COMPILE")
    {
        /*
         * @brief 检查顶点/片段着色器编译是否成功
         * @param shader: 要检查的着色器对象句柄
         */
        CHECK_GL_ERROR(glGetShaderiv(target, GL_COMPILE_STATUS, &success));
        if (!success)
        {
            CHECK_GL_ERROR(glGetShaderInfoLog(target, 512, nullptr, infoLog));
            std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    }
    else if (targetType == "LINK")
    {
        /*
         * @brief 检查着色器程序链接是否成功
         * @param program: 要检查的着色器程序对象句柄
         */
        CHECK_GL_ERROR(glGetProgramiv(target, GL_LINK_STATUS, &success));
        if (!success)
        {
            CHECK_GL_ERROR(glGetProgramInfoLog(target, 512, nullptr, infoLog));
            std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
    }
    else
    {
        std::cerr << "ERROR::SHADER::CHECK_ERROR::UNSUPPORTED_TARGET_TYPE" << std::endl;
    }
}
