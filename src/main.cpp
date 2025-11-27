#include <iostream>
#include <glad/glad.h> // note：glad头文件放在GLFW头文件之前，避免重复包含
#include <GLFW/glfw3.h>
#include "wrapper/ErrorChecker.h"

#define WINDOW_WIDTH 800  // 窗口宽度
#define WINDOW_HEIGHT 600 // 窗口高度
#define VIEWPORT_WIDTH 800  // 视口宽度
#define VIEWPORT_HEIGHT 600 // 视口高度

/* 窗口大小变化回调函数
 *@param window: 窗口对象指针
 *@param width: 窗口宽度
 *@param height: 窗口高度
 */
void FrameBufferSizeCallback(GLFWwindow* window, const int width, const int height)
{
    glViewport(0, 0, width, height); // 更新视口大小
}

/* 键盘输入回调函数
 *@param key: 键盘键值
 *@param scancode: 键盘扫描码
 *@param action: 键盘操作类型(GLFW_PRESS, GLFW_RELEASE, GLFW_REPEAT)
 *@param mods: 键盘修饰键(GLFW_MOD_SHIFT, GLFW_MOD_CONTROL, GLFW_MOD_ALT, GLFW_MOD_SUPER)
 */
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

}


int main()
{
    std::cout << "Hello, OpenGL!" << std::endl;

    //初始化GLFW的基本环境
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // 主版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6); // 次版本号
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 核心模式(非立即渲染模式)

    // 创建窗体对象
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "GLRenderer Window", nullptr, nullptr);
    glfwMakeContextCurrent(window); // 使当前线程的上下文成为指定的窗口上下文

    // 事件响应
    glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback); // 监听窗口大小变化事件
    glfwSetKeyCallback(window, KeyCallback); // 监听键盘输入事件

    // 初始化GLAD,加载当前OpenGL的所有函数
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // 设置视口大小及清除颜色
    CHECK_GL_ERROR(glViewport(0, 0, VIEWPORT_WIDTH, VIEWPORT_HEIGHT));
    CHECK_GL_ERROR(glClearColor(0.1f, 0.1f, 0.2f, 1.0f));

    // 执行窗体循环
    while (!glfwWindowShouldClose(window)) // 检查是否需要关闭窗口
    {
        // 处理事件，如键盘输入、鼠标移动等
        glfwPollEvents();

        // 清除颜色缓冲区
        CHECK_GL_ERROR(glClear(-1));

        // 交换缓冲区，将渲染结果显示在窗口上
        glfwSwapBuffers(window);
    }

        // 退出程序,清理GLFW环境,释放资源
    glfwDestroyWindow(window); // 销毁窗口对象
    glfwTerminate(); // 终止GLFW环境，释放资源

    return 0;
}