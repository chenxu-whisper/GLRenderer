#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Application.h"

Application::Application() = default;

Application::~Application() = default;

Application* Application::mInstance = nullptr;

// 获取单例实例
Application* Application::GetInstance()
{
    if (mInstance == nullptr)
        mInstance = new Application();

    return mInstance;
}

bool Application::WindowInit(const uint8_t& major, const uint8_t& minor,
                       const uint32_t& width, const uint32_t& height, const char *title)
{
    mWidth = width;
    mHeight = height;

    // 初始化GLFW的基本环境
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major); // 主版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor); // 次版本号
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 核心模式(非立即渲染模式)

    // 创建窗体对象
    mWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (mWindow == nullptr)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    // 使当前线程的上下文成为指定的窗口上下文
    glfwMakeContextCurrent(mWindow);

    // 初始化GLAD,加载当前OpenGL的所有函数
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    // 事件响应
    glfwSetFramebufferSizeCallback(mWindow, FramebufferSizeCallback); // 窗口大小改变回调函数
    glfwSetKeyCallback(mWindow, KeyCallback); // 键盘输入回调函数

    // 设置窗口用户指针,将当前应用实例指针绑定到窗口上
    glfwSetWindowUserPointer(mWindow, this);

    return true;
}

bool Application::WindowUpdate() const
{
    // 检查是否关闭窗口
    if (glfwWindowShouldClose(mWindow))
        return false;

    // 交换缓冲区
    glfwSwapBuffers(mWindow);
    // 处理事件
    glfwPollEvents();

    return true;
}

void Application::WindowDestroy() const
{
    // 销毁窗口
    glfwDestroyWindow(mWindow);
    // 终止GLFW
    glfwTerminate();

}

// 事件响应：窗口大小改变
void Application::SetResizeCallback(ResizeCallback callback) { mResizeCallback = callback; }
// 事件响应：键盘输入
void Application::SetKeyCallback(KeyBoardCallback callback) { mKeyCallback = callback; }

void Application::FramebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    std::cout << "Framebuffer size: " << width << " x " << height << std::endl;

    // 获取当前应用实例指针
    Application* self = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (self != nullptr)
        self->mResizeCallback(width, height);
}

void Application::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    Application* self = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (self != nullptr)
        self->mKeyCallback(key, scancode, action, mods);
}
