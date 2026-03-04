#include "Core.h"
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

bool Application::WindowInit(const uint8_t& major, const uint8_t& minor, const uint32_t& width, const uint32_t& height, const char *title)
{
    mWidth = width;
    mHeight = height;
    mTitle = title;

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

    // 初始化时设置带尺寸的窗口标题，格式为："窗口标题 (宽度 x 高度)"
    // todo: 与FramebufferSizeCallback重复，待优化
    char initialTitle[256];
    snprintf(initialTitle, sizeof(initialTitle), "%s (%d x %d)", title, width, height);
    glfwSetWindowTitle(mWindow, initialTitle);

    // 事件响应
    glfwSetFramebufferSizeCallback(mWindow, FramebufferSizeCallbackFunc); // 窗口大小改变回调函数
    glfwSetKeyCallback(mWindow, KeyCallbackFunc); // 键盘输入回调函数
    glfwSetMouseButtonCallback(mWindow, MouseButtonCallbackFunc); // 鼠标按钮回调函数
    glfwSetCursorPosCallback(mWindow, MouseMoveCallbackFunc); // 鼠标移动回调函数
    glfwSetScrollCallback(mWindow, MouseScrollCallbackFunc); // 鼠标滚轮回调函数

    // 设置窗口用户指针,将当前应用实例指针绑定到窗口上
    glfwSetWindowUserPointer(mWindow, this);

    return true;
}

uint32_t Application::GetWindowWidth() const { return mWidth; }

uint32_t Application::GetWindowHeight() const { return mHeight; }

void Application::GetCursorPos(double &x, double &y)
{
    glfwGetCursorPos(mWindow, &x, &y);
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

// 事件响应
void Application::SetResizeCallback(ResizeCallback callback) { mResizeCallback = callback; } // 窗口大小改变回调函数
void Application::SetKeyCallback(KeyBoardCallback callback) { mKeyCallback = callback; }  // 键盘输入回调函数
void Application::SetMouseCallback(MouseButtonCallback callback) { mMouseButtonCallback = callback; } // 鼠标按钮回调函数
void Application::SetCursorCallback(MouseMoveCallback callback) { mMouseMoveCallback = callback; } // 鼠标移动回调函数
void Application::SetScrollCallback(MouseScrollCallback callback) { mMouseScrollCallback = callback; } // 鼠标滚轮回调函数

// 回调函数实现
void Application::FramebufferSizeCallbackFunc(GLFWwindow *window, int width, int height)
{
    // 获取当前应用实例指针
    Application* self = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (self != nullptr)
    {
        // 使用保存的标题参数
        char title[256];
        snprintf(title, sizeof(title), "%s (%d x %d)", self->mTitle, width, height);
        glfwSetWindowTitle(window, title);

        self->mResizeCallback(width, height);
    }
}

void Application::KeyCallbackFunc(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    Application* self = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (self != nullptr)
        self->mKeyCallback(key, scancode, action, mods);
}

void Application::MouseButtonCallbackFunc(GLFWwindow* window, int button, int action, int mods)
{
    Application* self = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (self != nullptr && self->mMouseButtonCallback != nullptr)
        self->mMouseButtonCallback(button, action, mods);
}

void Application::MouseMoveCallbackFunc(GLFWwindow* window, double xpos, double ypos)
{
    Application* self = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (self != nullptr && self->mMouseMoveCallback != nullptr)
        self->mMouseMoveCallback(xpos, ypos);
}

void Application::MouseScrollCallbackFunc(GLFWwindow* window, double xoffset, double yoffset)
{
    // 忽略水平滚动
    xoffset = 0.0f;

    Application* self = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (self != nullptr && self->mMouseScrollCallback != nullptr)
        self->mMouseScrollCallback(xoffset, yoffset);
}