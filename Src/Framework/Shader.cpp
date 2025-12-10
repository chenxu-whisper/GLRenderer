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

    // 创建顶点/片元着色器
    CHECK_GL_ERROR(vertexShader = glCreateShader(GL_VERTEX_SHADER));
    CHECK_GL_ERROR(fragmentShader = glCreateShader(GL_FRAGMENT_SHADER));
    // 设置顶点/片元着色器源码
    CHECK_GL_ERROR(glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr));
    CHECK_GL_ERROR(glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr));
    // 编译顶点/片元着色器
    CHECK_GL_ERROR(glCompileShader(vertexShader));
    CHECK_GL_ERROR(glCompileShader(fragmentShader));

    // 检查顶点/片元着色器编译是否成功
    CheckShaderError(vertexShader, "COMPILE");
    CheckShaderError(fragmentShader, "COMPILE");

    // 创建着色器程序
    CHECK_GL_ERROR(mShaderProgram = glCreateProgram());
    // 绑定顶点着色器和片段着色器到着色器程序
    CHECK_GL_ERROR(glAttachShader(mShaderProgram, vertexShader));
    CHECK_GL_ERROR(glAttachShader(mShaderProgram, fragmentShader));
    // 链接着色器程序
    CHECK_GL_ERROR(glLinkProgram(mShaderProgram));
    // 检查着色器程序链接是否成功
    CheckShaderError(mShaderProgram, "LINK");

    // 删除着色器
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
    CHECK_GL_ERROR(glUseProgram(0));
}

void Shader::SetFloatUniform(const std::string &name, float value) const
{
    GLint location = glGetUniformLocation(mShaderProgram, name.c_str());
    if (location == -1)
    {
        std::cerr << "ERROR::SHADER::UNIFORM::NOT_FOUND - Name: " << name << std::endl;
        return;
    }
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
    CHECK_GL_ERROR(glUniform1i(location, value));
}

void Shader::CheckShaderError(GLuint target, const std::string& targetType)
{
    GLint success;
    GLchar infoLog[512];

    if (targetType == "COMPILE")
    {
        CHECK_GL_ERROR(glGetShaderiv(target, GL_COMPILE_STATUS, &success));
        if (!success)
        {
            CHECK_GL_ERROR(glGetShaderInfoLog(target, 512, nullptr, infoLog));
            std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    }
    else if (targetType == "LINK")
    {
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
