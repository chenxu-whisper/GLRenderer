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