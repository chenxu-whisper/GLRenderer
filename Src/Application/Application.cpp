#include "Core.h"
#include "Application.h"

/**
 * @brief 单例模式：获取单例实例
 * @return Application* 单例实例指针
 */
std::unique_ptr<Application> Application::mInstance = nullptr;

/**
 * @brief 单例模式：获取单例实例
 * @return Application* 单例实例指针
 */
std::mutex Application::mInstanceMutex = std::mutex();

// 获取单例实例
Application* Application::GetInstance()
{
    // 加锁确保线程安全
    std::lock_guard<std::mutex> lock(mInstanceMutex);

    // 如果实例不存在，则创建新实例
    if (mInstance == nullptr)
        mInstance = std::make_unique<Application>();

    return mInstance.get();
}

uint32_t Application::GetWindowWidth() const { return mWidth; }

uint32_t Application::GetWindowHeight() const { return mHeight; }

void Application::GetCursorPos(double &x, double &y) const
{
    glfwGetCursorPos(mWindow, &x, &y);
}

bool Application::WindowInit(const uint8_t& major, const uint8_t& minor, const uint32_t& width, const uint32_t& height, const char *title)
{
    mWidth = width;
    mHeight = height;
    mTitle = title;

    // 初始化GLFW的基本环境, 参考GLFW文档：https://www.glfw.org/docs/latest/window.html#window_hints
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major); // 主版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor); // 次版本号
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 核心模式(非立即渲染模式)
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // 前向兼容模式, 必须设置为GL_TRUE, 否则在MacOS上会报错

    /**
     * @brief 创建一个GLFW窗口
     * @param width 窗口宽度
     * @param height 窗口高度
     * @param title 窗口标题
     * @param monitor 窗口所属的监视器, nullptr表示默认监视器
     * @param share 共享上下文, nullptr表示不共享上下文
     * @return GLFWwindow* 窗口指针
     */
    mWindow = glfwCreateWindow(mWidth, mHeight, mTitle, nullptr, nullptr);
    if (mWindow == nullptr)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        // 终止GLFW,释放所有资源
        glfwTerminate();

        return false;
    }

    /**
     * @brief 使当前线程的上下文成为指定的窗口上下文
     * @param window 窗口指针
     */
    glfwMakeContextCurrent(mWindow);

    /**
     * @brief 初始化GLAD,加载当前OpenGL的所有函数
     * @param loader 加载OpenGL函数指针的函数
     * @return true 初始化成功
     * @return false 初始化失败
     */
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    UpdateWindowTitleInfo(mTitle, mWidth, mHeight);

    // 事件响应
    glfwSetFramebufferSizeCallback(mWindow, FramebufferSizeCallbackFunc); // 窗口大小改变回调函数
    glfwSetKeyCallback(mWindow, KeyCallbackFunc); // 键盘输入回调函数
    glfwSetMouseButtonCallback(mWindow, MouseButtonCallbackFunc); // 鼠标按钮回调函数
    glfwSetCursorPosCallback(mWindow, CursorPosCallbackFunc); // 鼠标移动回调函数
    glfwSetScrollCallback(mWindow, MouseScrollCallbackFunc); // 鼠标滚轮回调函数

    // 设置窗口用户指针,将当前应用实例指针绑定到窗口上
    glfwSetWindowUserPointer(mWindow, this);

    return true;
}

bool Application::WindowUpdate() const
{
    // 检查是否关闭窗口
    if (glfwWindowShouldClose(mWindow))
        return false;

    // 处理事件
    glfwPollEvents();
    // 交换缓冲区,双缓冲(Double Buffer)机制, 防止图像闪烁
    glfwSwapBuffers(mWindow);

    return true;
}

void Application::UpdateWindowTitleInfo(const char *title, const uint32_t &width, const uint32_t &height) const
{
    // 初始化时设置带尺寸的窗口标题，格式为："窗口标题 (宽度 x 高度)"
    /*
     * @brief 用于安全格式化字符串的核心函数
     * @param str 目标字符串缓冲区
     * @param size 目标字符串缓冲区大小
     * @param format 格式化字符串
     * @param ... 格式化参数
     * @return int 格式化后的字符串长度
     */
    char titleInfo[256];
    snprintf(titleInfo, sizeof(titleInfo), "%s (%d x %d)", title, width, height);
    glfwSetWindowTitle(mWindow, titleInfo);
}

void Application::WindowDestroy() const
{
    // 销毁窗口
    glfwDestroyWindow(mWindow);
    // 终止GLFW
    glfwTerminate();

}

// 回调函数实现
/**
 * @brief 窗口大小改变回调函数
 * @param window 窗口指针
 * @param width 新的宽度
 * @param height 新的高度
 */
void Application::FramebufferSizeCallbackFunc(GLFWwindow *window, int width, int height)
{
    // 获取当前应用实例指针
    Application* self = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (self != nullptr)
    {
        self->UpdateWindowTitleInfo(self->mTitle, width, height);
        self->mResizeCallback(width, height);
    }
}

/**
 * @brief 键盘输入回调函数
 * @param window 窗口指针
 * @param key 键码
 * @param scancode 扫描码
 * @param action 操作类型(GLFW_PRESS, GLFW_RELEASE, GLFW_REPEAT)
 * @param mods 修饰键位(GLFW_MOD_SHIFT, GLFW_MOD_CONTROL, GLFW_MOD_ALT, GLFW_MOD_SUPER)
 */
void Application::KeyCallbackFunc(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    Application* self = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (self != nullptr)
        self->mKeyCallback(key, scancode, action, mods);
}

/**
 * @brief 鼠标按钮回调函数
 * @param window 窗口指针
 * @param button 鼠标按钮码(GLFW_MOUSE_BUTTON_LEFT, GLFW_MOUSE_BUTTON_RIGHT, GLFW_MOUSE_BUTTON_MIDDLE)
 * @param action 操作类型(GLFW_PRESS, GLFW_RELEASE)
 * @param mods 修饰键位(GLFW_MOD_SHIFT, GLFW_MOD_CONTROL, GLFW_MOD_ALT, GLFW_MOD_SUPER)
 */
void Application::MouseButtonCallbackFunc(GLFWwindow* window, int button, int action, int mods)
{
    Application* self = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (self != nullptr && self->mMouseButtonCallback != nullptr)
        self->mMouseButtonCallback(button, action, mods);
}

/**
 * @brief 鼠标移动回调函数
 * @param window 窗口指针
 * @param xpos 新的X坐标
 * @param ypos 新的Y坐标
 */
void Application::CursorPosCallbackFunc(GLFWwindow* window, double xpos, double ypos)
{
    Application* self = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (self != nullptr && self->mMouseMoveCallback != nullptr)
        self->mMouseMoveCallback(xpos, ypos);
}

/**
 * @brief 鼠标滚轮回调函数
 * @param window 窗口指针
 * @param xoffset 水平滚动偏移量
 * @param yoffset 垂直滚动偏移量
 */
void Application::MouseScrollCallbackFunc(GLFWwindow* window, double xoffset, double yoffset)
{
    // 忽略水平滚动
    xoffset = 0.0f;

    Application* self = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if (self != nullptr && self->mMouseScrollCallback != nullptr)
        self->mMouseScrollCallback(xoffset, yoffset);
}

// 事件响应
void Application::SetResizeCallback(ResizeCallback callback) { mResizeCallback = callback; } // 窗口大小改变回调函数
void Application::SetKeyCallback(KeyBoardCallback callback) { mKeyCallback = callback; }  // 键盘输入回调函数
void Application::SetMouseCallback(MouseButtonCallback callback) { mMouseButtonCallback = callback; } // 鼠标按钮回调函数
void Application::SetCursorCallback(MouseMoveCallback callback) { mMouseMoveCallback = callback; } // 鼠标移动回调函数
void Application::SetScrollCallback(MouseScrollCallback callback) { mMouseScrollCallback = callback; } // 鼠标滚轮回调函数
