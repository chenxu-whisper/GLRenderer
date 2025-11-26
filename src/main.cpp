#include <iostream>
#include <glad/glad.h> // note：glad头文件放在GLFW头文件之前，避免重复包含
#include <GLFW/glfw3.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main()
{
    std::cout << "Hello, OpenGL!" << std::endl;

    // ********** 创建窗体 **********
    // 1. 初始化GLFW的基本环境
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // 主版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6); // 次版本号
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 核心模式(非立即渲染模式)
    // 2. 创建窗体对象
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "GLRenderer", nullptr, nullptr); // 创建窗体对象
    glfwMakeContextCurrent(window); // 使当前线程的上下文成为指定的窗口上下文
    // 3. 执行窗体循环
    while (!glfwWindowShouldClose(window)) // 检查是否需要关闭窗口
    {
        glfwSwapBuffers(window); // 交换缓冲区，将渲染结果显示在窗口上
        glfwPollEvents(); // 处理事件，如键盘输入、鼠标移动等
    }
    // 4. 退出程序,清理GLFW环境,释放资源
    glfwDestroyWindow(window); // 销毁窗口对象
    glfwTerminate(); // 终止GLFW环境，释放资源
    // ****************************************

    return 0;
}