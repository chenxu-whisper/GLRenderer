#ifndef APPLICATON_H
#define APPLICATION_H

#include "Core.h"

// 应用实例访问宏
#define APP Application::GetInstance()

// 前置声明GLFWwindow，避免包含GLFW头文件
class GLFWwindow;

// 事件响应
using ResizeCallback = void(*)(int width, int height); // 窗口大小改变回调函数
using KeyBoardCallback = void(*)(int key, int scancode, int action, int mods); // 键盘输入回调函数
using MouseButtonCallback = void(*)(int button, int action, int mods); // 鼠标按钮回调函数
using MouseMoveCallback = void(*)(double xpos, double ypos); // 鼠标移动回调函数
using MouseScrollCallback = void(*)(double xoffset, double yoffset); // 鼠标滚轮回调函数

// 单例模式
class Application
{
public:
    ~Application();
    // 获取单例实例
    static Application* GetInstance();
    // 初始化窗口
    bool WindowInit(const uint8_t& major = 4, const uint8_t& minor = 6, const uint32_t& width = 800, const uint32_t& height = 600, const char* title = "Window");
    // 获取窗口宽度
    uint32_t GetWindowWidth() const;
    // 获取窗口高度
    uint32_t GetWindowHeight() const;
    // 获取鼠标位置
    void GetCursorPos(double& x, double& y);
    // 更新窗口
    bool WindowUpdate() const;
    // 销毁窗口
    void WindowDestroy() const;
    // 设置窗口大小改变回调函数
    void SetResizeCallback(ResizeCallback callback);
    // 设置键盘输入回调函数
    void SetKeyCallback(KeyBoardCallback callback);
    // 添加鼠标事件回调函数设置
    void SetMouseCallback(MouseButtonCallback callback);
    void SetCursorCallback(MouseMoveCallback callback);
    void SetScrollCallback(MouseScrollCallback callback);

private:
    /* @note: 需要用static，静态成员函数没有隐式的this指针（C++类内函数指针）:
     *  1. GLFW期望的回调函数类型是GLFWframebuffersizefun，即普通函数指针void (*)(GLFWwindow*, int, int)
     *  2. C++类的非静态成员函数有一个隐式的this指针参数，所以类型实际上是void (Application::*)(GLFWwindow*, int, int),这里的Application::是指的作用域不是调用函数
     *  3. 这两种类型不兼容，不能直接转换。为了在回调函数中调用类的成员函数，需要将回调函数设为静态成员函数
     */

    /* 窗口大小变化回调函数
     *@param window: 窗口对象指针
     *@param width: 窗口宽度
     *@param height: 窗口高度
     */
    static void FramebufferSizeCallbackFunc(GLFWwindow* window, int width, int height);
    /* 键盘输入回调函数
     *@param key: 键盘键值
     *@param scancode: 键盘扫描码
     *@param action: 键盘操作类型(GLFW_PRESS, GLFW_RELEASE, GLFW_REPEAT)
     *@param mods: 键盘修饰键(GLFW_MOD_SHIFT, GLFW_MOD_CONTROL, GLFW_MOD_ALT, GLFW_MOD_SUPER)
     */
    static void KeyCallbackFunc(GLFWwindow* window, int key, int scancode, int action, int mods);
    /* 鼠标按钮回调函数
    *@param window: 窗口对象指针
    *@param button: 鼠标按钮
    *@param action: 操作类型
    *@param mods: 修饰键
    */
    static void MouseButtonCallbackFunc(GLFWwindow* window, int button, int action, int mods);
    /* 鼠标移动回调函数
     *@param window: 窗口对象指针
     *@param xpos: X坐标位置
     *@param ypos: Y坐标位置
     */
    static void MouseMoveCallbackFunc(GLFWwindow* window, double xpos, double ypos);
    /* 鼠标滚轮回调函数
     *@param window: 窗口对象指针
     *@param xoffset: X方向偏移
     *@param yoffset: Y方向偏移
     */
    static void MouseScrollCallbackFunc(GLFWwindow* window, double xoffset, double yoffset);

private:
    // 构造函数设为私有，防止外部实例化
    Application();
    // 单例实例指针
    static Application* mInstance;
    // 窗口
    GLFWwindow* mWindow = nullptr;
    uint32_t mWidth = 0;
    uint32_t mHeight = 0;
    const char* mTitle = nullptr;
    // 事件响应
    ResizeCallback mResizeCallback = nullptr;
    KeyBoardCallback mKeyCallback = nullptr;
    MouseButtonCallback mMouseButtonCallback = nullptr;
    MouseMoveCallback mMouseMoveCallback = nullptr;
    MouseScrollCallback mMouseScrollCallback = nullptr;
};


#endif //APPLICATON_H
