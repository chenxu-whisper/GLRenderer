
#include <iostream>
#include <string>
#include <assert.h>
#include <glad/glad.h>
#include "ErrorChecker.h"

// 检查OpenGL错误
void ErrorChecker()
{
    GLenum error = glGetError();
    std::string error_msg = "";
    if (error != GL_NO_ERROR)
    {
        switch (error)
        {
            case GL_INVALID_ENUM: error_msg = "GL_INVALID_ENUM : 枚举参数超出范围"; break;
            case GL_INVALID_VALUE: error_msg = "GL_INVALID_VALUE : 参数超出范围"; break;
            case GL_INVALID_OPERATION: error_msg = "GL_INVALID_OPERATION : 操作数与当前状态不兼容"; break;
            case GL_OUT_OF_MEMORY: error_msg = "GL_OUT_OF_MEMORY : 内存不足"; break;
            default: error_msg = "Unknown OpenGL Error : 未知错误"; break;
        }
        std::cerr << error_msg << std::endl;

        assert(false);  // assert根据传入的bool值决定程序是否终止
    }
}
