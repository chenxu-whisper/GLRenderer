#include <iostream>
#include <glad/glad.h> // note：glad头文件放在GLFW头文件之前，避免重复包含
#include <GLFW/glfw3.h>
#include "wrapper/ErrorChecker.h"
#include "application/Application.h"

// 窗体参数
#define MAJOR_VERSION 4 // OpenGL主版本号
#define MINOR_VERSION 6 // OpenGL次版本号
#define WINDOW_WIDTH 800  // 窗口宽度
#define WINDOW_HEIGHT 600 // 窗口高度
#define WINDOW_TITLE "GLRenderer Window"  // 窗口标题
#define VIEWPORT_WIDTH 800  // 视口宽度
#define VIEWPORT_HEIGHT 600 // 视口高度


/* 顶点数据 （位置 + 颜色）
 * 每个顶点由位置（3个float）和颜色（3个float）组成
 * stride：每个顶点的步长，即从一个顶点的位置数据开始，到下一个顶点的位置数据的字节偏移量。每个顶点占用6个float， stride = 6 * sizeof(float) = 24
 * offset：每个顶点的颜色数据在顶点数组中的字节偏移量。颜色数据紧跟在位置数据后面，offset = 0（位置） + 3 * sizeof(float)（颜色） = 12
*/
const float verties[] =
{
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // 左下
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // 右下
     0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f  // 顶部
};

// 事件操作
void OnWindowResizeEvent(int width, int height)
{
    // 更新视口大小
    CHECK_GL_ERROR(glViewport(0, 0, width, height));
}

void OnKeyBoardEvent(int key, int scancode, int action, int mods)
{
    // 检查是否按下了ESC键
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
    {
        std::cout << "Space key pressed!" << std::endl;
    }
}

void OnMouseButtonEvent(int button, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        switch (button)
        {
            case GLFW_MOUSE_BUTTON_LEFT:
                std::cout << "Left mouse button pressed!" << std::endl;
                break;
            case GLFW_MOUSE_BUTTON_RIGHT:
                std::cout << "Right mouse button pressed!" << std::endl;
                break;
            case GLFW_MOUSE_BUTTON_MIDDLE:
                std::cout << "Middle mouse button pressed!" << std::endl;
                break;
            default: break;
        }
    }
    else if (action == GLFW_RELEASE)
    {
        switch (button)
        {
            case GLFW_MOUSE_BUTTON_LEFT:
                std::cout << "Left mouse button released!" << std::endl;
                break;
            case GLFW_MOUSE_BUTTON_RIGHT:
                std::cout << "Right mouse button released!" << std::endl;
                break;
            case GLFW_MOUSE_BUTTON_MIDDLE:
                std::cout << "Middle mouse button released!" << std::endl;
                break;
            default: break;
        }
    }
}

void OnMouseMoveEvent(double xpos, double ypos)
{
    // 输出鼠标位置信息
    std::cout << "Mouse position: (" << xpos << ", " << ypos << ")" << std::endl;
}

void OnMouseScrollEvent(double xoffset, double yoffset)
{
    // 输出鼠标滚轮信息
    std::cout << "Mouse scroll: (" << xoffset << ", " << yoffset << ")" << std::endl;
}

void Prepare()
{
    // 生成VBO
    GLuint VBO = 0;
    CHECK_GL_ERROR(glGenBuffers(1, &VBO));
    /* 绑定VBO到当前OpenGL状态机的当前VBO插槽
     * GL_ARRAY_BUFFER: 表示当前VBO这个插槽
     */
    CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, VBO));
    /* 开辟显存空间，向VBO传输数据
     * GL_STATIC_DRAW：表示数据将被使用多次，且不会被修改
     * GL_DYNAMIC_DRAW：数据会被改变很多。
     * GL_STREAM_DRAW ：数据每次绘制时都会改变。
     */
    CHECK_GL_ERROR(glBufferData(GL_ARRAY_BUFFER, sizeof(verties), verties, GL_STATIC_DRAW));

    // 生成VAO
    GLuint VAO = 0;
    CHECK_GL_ERROR(glGenVertexArrays(1, &VAO));
    // 绑定VBO到当前OpenGL状态机的当前VAO插槽
    CHECK_GL_ERROR(glBindVertexArray(VAO));
    // 启用顶点属性数组，索引为0：position, 在vertex shader中layout(location = 0)指定
    CHECK_GL_ERROR(glEnableVertexAttribArray(0));
    // 设置顶点属性指针，索引为0，属性为3个float，步长为24个字节，偏移量为0个字节
    CHECK_GL_ERROR(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, reinterpret_cast<void *>(0)));
    // 启用顶点属性数组，索引为1：color, 在vertex shader中layout(location = 1)指定
    CHECK_GL_ERROR(glEnableVertexAttribArray(1));
    // 设置顶点属性指针，索引为1，属性为3个float，步长为24个字节，偏移量为12个字节
    CHECK_GL_ERROR(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, reinterpret_cast<void *>(sizeof(float) * 3)));

    // 解绑VAO, VBO
    CHECK_GL_ERROR(glBindVertexArray(0));
    CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

bool CreateWindow()
{
    // 初始化窗口
    if (!APP->WindowInit(MAJOR_VERSION, MINOR_VERSION, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE))
    {
        std::cerr << "Failed to initialize GLFW window" << std::endl;
        return false;
    }
    // 事件响应：窗口大小改变
    APP->SetResizeCallback(OnWindowResizeEvent);
    APP->SetKeyCallback(OnKeyBoardEvent);
    // 设置鼠标事件回调
    APP->SetMouseButtonCallback(OnMouseButtonEvent);
    APP->SetMouseMoveCallback(OnMouseMoveEvent);
    APP->SetMouseScrollCallback(OnMouseScrollEvent);
    // 准备VBO数据
    Prepare();
    // 设置视口大小及清除颜色
    CHECK_GL_ERROR(glViewport(0, 0, VIEWPORT_WIDTH, VIEWPORT_HEIGHT));
    CHECK_GL_ERROR(glClearColor(0.1f, 0.1f, 0.2f, 1.0f));
    // 执行渲染循环
    while (APP->WindowUpdate())
    {
        // 清除颜色缓冲区
        CHECK_GL_ERROR(glClear(GL_COLOR_BUFFER_BIT));
    }
    // 销毁窗口
    APP->WindowDestroy();

    return true;
}


int main()
{
    std::cout << "Hello, OpenGL!" << std::endl;

    if (!CreateWindow())
    {
        std::cerr << "Failed to create window" << std::endl;
        return -1;
    }

    return 0;
}