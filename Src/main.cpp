#include "Core.h"
#include "Application/Texture.h"
#include "Application/Application.h"
#include "Framework/Shader.h"
#include "Application/Camera/PerspectiveCamera.h"
#include "Application/Camera/OrthographicCamera.h"
#include "Application/Camera/TrackBallCameraControl.h"
#include "Application/Camera/GameCameraControl.h"

// 窗体参数
#define MAJOR_VERSION 4 // OpenGL主版本号
#define MINOR_VERSION 6 // OpenGL次版本号
#define WINDOW_WIDTH 800  // 窗口宽度
#define WINDOW_HEIGHT 600 // 窗口高度
#define WINDOW_TITLE "GLRenderer Window"  // 窗口标题
#define VIEWPORT_WIDTH 800  // 视口宽度
#define VIEWPORT_HEIGHT 600 // 视口高度


/*顶点数据 （位置 + 颜色）
 * 每个顶点由位置（3个float）和颜色（3个float）组成和纹理坐标（2个float）
 * stride：每个顶点的步长，即从一个顶点的位置数据开始，到下一个顶点的位置数据的字节偏移量。每个顶点占用8个float， stride = 6 * sizeof(float) = 32
 * offset：每个顶点的颜色数据在顶点数组中的字节偏移量。颜色数据紧跟在位置数据后面，offset = 0（位置） + 3 * sizeof(float)（颜色） = 12
*/
constexpr float vertices[] = {
    // 位置（3个float）   //颜色（3个float）  // 纹理坐标（2个float）
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // 左下
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // 右下
     0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 1.0f  // 顶部
};


/**
 * 矩形数据 （位置 + 颜色 + 纹理坐标）
 * 每个顶点由位置（3个float）、颜色（3个float）和纹理坐标（2个float）组成
*/
constexpr float rect[] =
{
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // 左下
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // 右下
     0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // 顶部
    -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // 左上
};

const unsigned int indices[] =
{
    0, 1, 2, // 第一个三角形
    2, 3, 0 // 第二个三角形
};

// 准备VAO, VBO
GLuint triangleVAO = 0;
void PrepareTriangleData()
{
    // 生成VBO
    GLuint VBO = 0;
    /* 生成VBO缓冲区对象
     * @param n: 要生成的缓冲区对象数量，这里是1
     * @param buffers: 指向GLuint数组的指针，用于存储生成的缓冲区对象ID
     */
    CHECK_GL_ERROR(glGenBuffers(1, &VBO));
    /* 绑定VBO到当前OpenGL状态机的当前VBO插槽
     * @param target: 目标缓冲区类型，这里是GL_ARRAY_BUFFER，即顶点缓冲区
     * @param buffer: 要绑定的缓冲区对象的ID，这里是VBO
     */
    CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, VBO));
    /* 开辟显存空间，向VBO传输数据
     * @param target: 目标缓冲区类型，这里是GL_ARRAY_BUFFER，即顶点缓冲区
     * @param size: 要传输的数据大小，这里是sizeof(vertices)，即顶点数组的大小
     * @param data: 指向要传输数据的指针，这里是vertices
     * @param usage: 数据的使用模式
         * GL_STATIC_DRAW：表示数据将被使用多次，且不会被修改
         * GL_DYNAMIC_DRAW：数据会被改变很多。
         * GL_STREAM_DRAW ：数据每次绘制时都会改变。
     */
    CHECK_GL_ERROR(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

    // 生成VAO
    // GLuint VAO = 0;
    /* 生成VAO缓冲区对象
     * @param n: 要生成的缓冲区对象数量，这里是1
     * @param arrays: 指向GLuint数组的指针，用于存储生成的缓冲区对象ID
     */
    CHECK_GL_ERROR(glGenVertexArrays(1, &triangleVAO));
    /* 绑定VAO到当前OpenGL状态机的当前VAO插槽
     * @param array: 要绑定的缓冲区对象的ID，这里是VAO
     */
    CHECK_GL_ERROR(glBindVertexArray(triangleVAO));
    /* 启用顶点属性数组，索引为0：position, 在vertex shader中layout(location = 0)指定
     * @param index: 顶点属性索引，对应vertex shader中的layout(location = index)
     */
    CHECK_GL_ERROR(glEnableVertexAttribArray(0));
    /* 设置顶点属性指针，索引为0，属性为3个float，步长为32个字节，偏移量为0个字节
     * @param index: 顶点属性索引，对应vertex shader中的layout(location = index)
     * @param size: 每个顶点属性的组件数量，这里是3个float，即vec3
     * @param type: 数据类型，这里是GL_FLOAT，每个组件占用4个字节
     * @param normalized: 是否归一化，这里是GL_FALSE
     * @param stride: 每个顶点的步长，即从一个顶点的位置数据开始，到下一个顶点的位置数据的字节偏移量。每个顶点占用8个float， stride = 8 * sizeof(float) = 32
     * @param offset: 每个顶点的位置数据在顶点数组中的字节偏移量。位置数据在顶点数组的开头，offset = 0
     */
    CHECK_GL_ERROR(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, reinterpret_cast<void *>(0)));
    // 启用顶点属性数组，索引为1：color, 在vertex shader中layout(location = 1)指定
    CHECK_GL_ERROR(glEnableVertexAttribArray(1));
    /* 设置顶点属性指针，索引为1，属性为3个float，步长为32个字节，偏移量为12个字节
     * @param index: 顶点属性索引，对应vertex shader中的layout(location = index)
     * @param size: 每个顶点属性的组件数量，这里是3个float，即vec3
     * @param type: 数据类型，这里是GL_FLOAT，每个组件占用4个字节
     * @param normalized: 是否归一化，这里是GL_FALSE
     * @param stride: 每个顶点的步长，即从一个顶点的颜色数据开始，到下一个顶点的颜色数据的字节偏移量。每个顶点占用8个float， stride = 8 * sizeof(float) = 32
     * @param offset: 每个顶点的颜色数据在顶点数组中的字节偏移量。颜色数据在顶点数组的第3个float开始，offset = sizeof(float) * 3
     */
    CHECK_GL_ERROR(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, reinterpret_cast<void *>(sizeof(float) * 3)));
    // 启用顶点属性数组，索引为2：texCoord, 在vertex shader中layout(location = 2)指定
    CHECK_GL_ERROR(glEnableVertexAttribArray(2));
    /* 设置顶点属性指针，索引为2，属性为2个float，步长为24个字节，偏移量为24个字节
     * @param index: 顶点属性索引，对应vertex shader中的layout(location = index)
     * @param size: 每个顶点属性的组件数量，这里是2个float，即vec2
     * @param type: 数据类型，这里是GL_FLOAT，每个组件占用4个字节
     * @param normalized: 是否归一化，这里是GL_FALSE
     * @param stride: 每个顶点的步长，即从一个顶点的纹理坐标数据开始，到下一个顶点的纹理坐标数据的字节偏移量。每个顶点占用8个float， stride = 8 * sizeof(float) = 32
     * @param offset: 每个顶点的纹理坐标数据在顶点数组中的字节偏移量。纹理坐标数据在顶点数组的第6个float开始，offset = sizeof(float) * 6
     */
    CHECK_GL_ERROR(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, reinterpret_cast<void *>(sizeof(float) * 6)));

    // 解绑VAO, VBO, EBO
    /* 解绑VAO到当前OpenGL状态机的当前VAO插槽
     * @param array: 要解绑的缓冲区对象的ID，这里是VAO
     */
    CHECK_GL_ERROR(glBindVertexArray(0));
    /* 解绑VBO到当前OpenGL状态机的当前ARRAY_BUFFER插槽
     * @param buffer: 要解绑的缓冲区对象的ID，这里是VBO
     */
    CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

GLuint rectangleVAO = 0;
void PrepareRectangleData()
{
    // 生成VBO
    GLuint VBO = 0;
    /* 生成VBO缓冲区对象
     * @param n: 要生成的缓冲区对象数量，这里是1
     * @param buffers: 指向GLuint数组的指针，用于存储生成的缓冲区对象ID
     */
    CHECK_GL_ERROR(glGenBuffers(1, &VBO));
    /* 绑定VBO到当前OpenGL状态机的当前VBO插槽
     * @param target: 目标缓冲区类型，这里是GL_ARRAY_BUFFER，即顶点缓冲区
     * @param buffer: 要绑定的缓冲区对象的ID，这里是VBO
     */
    CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, VBO));
    /* 开辟显存空间，向VBO传输数据
     * @param target: 目标缓冲区类型，这里是GL_ARRAY_BUFFER，即顶点缓冲区
     * @param size: 要传输的数据大小，这里是sizeof(vertices)，即顶点数组的大小
     * @param data: 指向要传输数据的指针，这里是vertices
     * @param usage: 数据的使用模式
         * GL_STATIC_DRAW：表示数据将被使用多次，且不会被修改
         * GL_DYNAMIC_DRAW：数据会被改变很多。
         * GL_STREAM_DRAW ：数据每次绘制时都会改变。
     */
    CHECK_GL_ERROR(glBufferData(GL_ARRAY_BUFFER, sizeof(rect), rect, GL_STATIC_DRAW));

    // 生成EBO
    GLuint EBO = 0;
    /* 生成EBO缓冲区对象
     * @param n: 要生成的缓冲区对象数量，这里是1
     * @param buffers: 指向GLuint数组的指针，用于存储生成的缓冲区对象ID
     */
    CHECK_GL_ERROR(glGenBuffers(1, &EBO));
    /* 绑定EBO到当前OpenGL状态机的当前EBO插槽，此时VAO尚未创建或绑定, 因此EBO需要在VAO绑定状态下绑定, 因为VAO还未绑定，所以这个EBO绑定状态只是临时用于数据传输
     * @param target: 目标缓冲区类型，这里是GL_ELEMENT_ARRAY_BUFFER，即索引缓冲区
     * @param buffer: 要绑定的缓冲区对象的ID，这里是EBO
     */
    CHECK_GL_ERROR(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
    /* 开辟显存空间，向EBO传输数据
     * @param target: 目标缓冲区类型，这里是GL_ELEMENT_ARRAY_BUFFER，即索引缓冲区
     * @param size: 要传输的数据大小，这里是sizeof(indices)，即索引数组的大小
     * @param data: 指向要传输数据的指针，这里是indices
     * @param usage: 数据的使用模式
         * GL_STATIC_DRAW：表示数据将被使用多次，且不会被修改
         * GL_DYNAMIC_DRAW：数据会被改变很多。
         * GL_STREAM_DRAW ：数据每次绘制时都会改变。
     */
    CHECK_GL_ERROR(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

    // 生成VAO, 先绑定VAO
    /* 生成VAO缓冲区对象
     * @param n: 要生成的缓冲区对象数量，这里是1
     * @param arrays: 指向GLuint数组的指针，用于存储生成的缓冲区对象ID
     */
    CHECK_GL_ERROR(glGenVertexArrays(1, &rectangleVAO));
    /* 绑定VAO到当前OpenGL状态机的当前VAO插槽
     * @param array: 要绑定的缓冲区对象的ID，这里是rectangleVAO
     */
    CHECK_GL_ERROR(glBindVertexArray(rectangleVAO));

    // 确保VBO在VAO绑定后再次绑定
    CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, VBO));

    /* 启用顶点属性数组，索引为0：position, 在vertex shader中layout(location = 0)指定
     * @param index: 顶点属性索引，对应vertex shader中的layout(location = index)
     */
    CHECK_GL_ERROR(glEnableVertexAttribArray(0));
    /* 设置顶点属性指针，索引为0，属性为3个float，步长为24个字节，偏移量为0个字节
     * @param index: 顶点属性索引，对应vertex shader中的layout(location = index)
     * @param size: 每个顶点属性的组件数量，这里是3个float，即vec3
     * @param type: 数据类型，这里是GL_FLOAT，每个组件占用4个字节
     * @param normalized: 是否归一化，这里是GL_FALSE
     * @param stride: 每个顶点的步长，即从一个顶点的位置数据开始，到下一个顶点的位置数据的字节偏移量。每个顶点占用8个float， stride = 8 * sizeof(float) = 32
     * @param offset: 每个顶点的位置数据在顶点数组中的字节偏移量。位置数据在顶点数组的开头，offset = 0
     */
    CHECK_GL_ERROR(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, reinterpret_cast<void *>(0)));
    /* 启用顶点属性数组，索引为1：color, 在vertex shader中layout(location = 1)指定
     * @param index: 顶点属性索引，对应vertex shader中的layout(location = index)
     */
    CHECK_GL_ERROR(glEnableVertexAttribArray(1));
    /* 设置顶点属性指针，索引为1，属性为3个float，步长为24个字节，偏移量为12个字节
     * @param index: 顶点属性索引，对应vertex shader中的layout(location = index)
     * @param size: 每个顶点属性的组件数量，这里是3个float，即vec3
     * @param type: 数据类型，这里是GL_FLOAT，每个组件占用4个字节
     * @param normalized: 是否归一化，这里是GL_FALSE
     * @param stride: 每个顶点的步长，即从一个顶点的位置数据开始，到下一个顶点的位置数据的字节偏移量。每个顶点占用8个float， stride = 8 * sizeof(float) = 32
     * @param offset: 每个顶点的颜色数据在顶点数组中的字节偏移量。颜色数据在顶点数组的第3个float开始，offset = sizeof(float) * 3 = 12
     */
    CHECK_GL_ERROR(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, reinterpret_cast<void *>(sizeof(float) * 3)));
    CHECK_GL_ERROR(glEnableVertexAttribArray(2));
    CHECK_GL_ERROR(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, reinterpret_cast<void *>(sizeof(float) * 6)));

    // 然后绑定EBO, 只有在VAO绑定状态下的EBO绑定才会被VAO永久记录, 才能确保索引数据与顶点配置正确关联，实现正确的图元绘制。
    CHECK_GL_ERROR(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));

    // 解绑VAO和VBO，但不要解绑EBO（它应该保持与VAO的关联）
    CHECK_GL_ERROR(glBindVertexArray(0));
    CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, 0));
    // 注意：不要在这里解绑EBO，解绑这会导致VAO记录一个无效的EBO绑定（0）, 后续绘制时会使用默认的EBO（0）, 导致绘制错误
}

glm::mat4x4 triangleModelMat = glm::mat4x4(1.0f);
glm::mat4x4 rectangleModelMat = glm::mat4x4(1.0f);
void TriangleTransform()
{
    /* 平移变换
     * @param transMat: 平移变换矩阵
     * @param transVec: 平移向量，这里是(0.5f, -0.5f, 0.0f)
     */
    auto transMat = glm::mat4x4(1.0f);
    transMat = glm::translate(transMat, glm::vec3(0.5f, 0.5f, 0.1f));

    /* 缩放变换
     * @param scaleMat: 缩放变换矩阵
     * @param scaleVec: 缩放向量，这里是(0.5f, 0.5f, 1.0f)
     */
    auto scaleMat = glm::mat4x4(1.0f);
    scaleMat = glm::scale(scaleMat, glm::vec3(0.5f, 0.5f, 1.0f));

    /* 旋转变换
     * @param rotateMat: 旋转变换矩阵
     * @param angle: 旋转角度，这里是glfwGetTime()，即当前时间，单位为秒
     * @param axis: 旋转轴，这里是(0.0f, 0.0f, 1.0f)，即绕Z轴旋转
     */
    auto rotateMat = glm::mat4x4(1.0f);
    rotateMat = glm::rotate(rotateMat, static_cast<float>(glfwGetTime()), glm::vec3(0.0f, 0.0f, 1.0f));

    // 变换矩阵
    triangleModelMat = transMat;
}

Camera* camera = nullptr;
CameraControl* cameraControl = nullptr;
void PrepareCamera()
{
    camera = new PerspectiveCamera(60.0f, static_cast<float>(APP->GetWindowWidth()) / static_cast<float>(APP->GetWindowHeight()), 0.01f, 100.0f);
    // camera = new OrthographicCamera(-1.0f, 1.0f, -1.0f, 1.0f, 0.01f, 100.0f);
    cameraControl = new TrackBallCameraControl();
    // cameraControl = new GameCameraControl();
    cameraControl->SetCamera(camera);
    cameraControl->SetSensitivity(0.1f);
}

// 事件操作
void OnWindowResizeEvent(int width, int height)
{
    // 更新视口大小
    CHECK_GL_ERROR(glViewport(0, 0, width, height));
}

void OnKeyEvent(int key, int scancode, int action, int mods)
{
    // 处理相机控制
    cameraControl->OnKey(key, action, mods);

    // 检查是否按下了Space键
    // if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
    // {
    //     std::cout << "Space key pressed!" << std::endl;
    // }
}

void OnMouseEvent(int button, int action, int mods)
{
    double xpos, ypos;
    APP->GetCursorPos(xpos, ypos);
    // 处理相机控制
    cameraControl->OnMouse(button, action, xpos, ypos);

    // if (action == GLFW_PRESS)
    // {
    //     switch (button)
    //     {
    //         case GLFW_MOUSE_BUTTON_LEFT:
    //             std::cout << "Left mouse button pressed!" << std::endl;
    //             break;
    //         case GLFW_MOUSE_BUTTON_RIGHT:
    //             std::cout << "Right mouse button pressed!" << std::endl;
    //             break;
    //         case GLFW_MOUSE_BUTTON_MIDDLE:
    //             std::cout << "Middle mouse button pressed!" << std::endl;
    //             break;
    //         default: break;
    //     }
    // }
    // else if (action == GLFW_RELEASE)
    // {
    //     switch (button)
    //     {
    //         case GLFW_MOUSE_BUTTON_LEFT:
    //             std::cout << "Left mouse button released!" << std::endl;
    //             break;
    //         case GLFW_MOUSE_BUTTON_RIGHT:
    //             std::cout << "Right mouse button released!" << std::endl;
    //             break;
    //         case GLFW_MOUSE_BUTTON_MIDDLE:
    //             std::cout << "Middle mouse button released!" << std::endl;
    //             break;
    //         default: break;
    //     }
    // }
}

void OnCursorEvent(double xpos, double ypos)
{
    // 处理相机控制
    cameraControl->OnCursor(xpos, ypos);

    // // 输出鼠标位置信息
    // std::cout << "Mouse position: (" << xpos << ", " << ypos << ")" << std::endl;
}

void OnScrollEvent(double xoffset, double yoffset)
{
    // 忽略水平滚动
    xoffset = 0.0f;
    // 处理相机控制
    cameraControl->OnScroll(xoffset, yoffset);
}

void PrepareState()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}

// 渲染
std::unique_ptr<Shader> shaderTriangle;
std::unique_ptr<Shader> shaderRectangle;
std::unique_ptr<Texture> textureTriangle;
std::unique_ptr<Texture> textureRectangle;
void Render()
{
    /* 清除颜色缓冲区，将颜色缓冲区的颜色设置为指定的颜色值
     * @param mask: 要清除的缓冲区位掩码，这里是GL_COLOR_BUFFER_BIT，即颜色缓冲区
     */
    CHECK_GL_ERROR(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    // shader
    shaderTriangle->UseShaderProgram();
    // shader->SetFloatUniform("uTime", static_cast<float>(glfwGetTime())); // glfwGetTime()返回当前时间，单位为秒
    shaderTriangle->SetIntUniform("uColorTexture", 0);
    shaderTriangle->SetVec4Uniform("uColor", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    shaderTriangle->SetMat4x4Uniform("uModelMatrix", triangleModelMat);
    shaderTriangle->SetMat4x4Uniform("uViewMatrix", camera->GetViewMatrix());
    shaderTriangle->SetMat4x4Uniform("uProjectionMatrix", camera->GetProjectionMatrix());

    // 绘制三角形
    /* 绑定VAO，将指定的VAO绑定到当前OpenGL状态机，后续的顶点属性配置和索引绘制操作将使用该VAO的状态
     * @param vao: 要绑定的VAO ID，这里是triangleVAO
     */
    CHECK_GL_ERROR(glBindVertexArray(triangleVAO));
    /* 绘制三角形，使用顶点缓冲区绘制三角形图元
     * @Param mode： 要绘制的图元类型
         * GL_POINTS：每个顶点单独画一个点
         * GL_LINES：绘制线段图元, 每2个顶点画一个线段（顶点数需为 2 的倍数）
         * GL_LINE_STRIP：绘制折线图元, 每2个顶点画一条线段（顶点数需为 2 的倍数）
         * GL_TRIANGLES：绘制三角形图元, 每3个顶点画一个三角形（顶点数需为 3 的倍数）
         * GL_LINE_STRIP：：三角带（相邻 3 个顶点组成三角形，如顶点 0-1-2、1-2-3… 节省顶点）
         * GL_TRIANGLE_FAN：三角扇（以第一个顶点为中心，如 0-1-2、0-2-3… 适合画圆形/扇形）
     * @Param first： 要绘制的第一个顶点索引
     * @Param count： 要绘制的顶点数量
     */
    CHECK_GL_ERROR(glDrawArrays(GL_TRIANGLES, 0, 3));

    // 绘制矩形
    shaderRectangle->UseShaderProgram();
    shaderRectangle->SetVec4Uniform("uColor", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    shaderRectangle->SetMat4x4Uniform("uModelMatrix", rectangleModelMat);
    shaderRectangle->SetIntUniform("uColorTexture", 1);
    shaderRectangle->SetMat4x4Uniform("uViewMatrix", camera->GetViewMatrix());
    shaderRectangle->SetMat4x4Uniform("uProjectionMatrix", camera->GetProjectionMatrix());

    /* 绑定VAO，将指定的VAO绑定到当前OpenGL状态机，后续的顶点属性配置和索引绘制操作将使用该VAO的状态
     * @param vao: 要绑定的VAO ID，这里是rectangleVAO
     */
    CHECK_GL_ERROR(glBindVertexArray(rectangleVAO));
    /* 绘制矩形，使用索引缓冲区绘制矩形图元
     * @Param mode： 要绘制的图元类型，这里是GL_TRIANGLES，即三角形图元
     * @Param count： 要绘制的索引数量，这里是6，即绘制6个索引对应的三角形
     * @Param type： 索引数据的类型，这里是GL_UNSIGNED_INT，即无符号整数类型
     * @Param indices： 指向索引数据的指针，这里是nullptr，因为索引数据已经绑定到EBO
        * 如果使用EBO，参数为nullptr(0)
        * 如果使用EBO，参数为数字，表示EBO的偏移量（单位为字节）
        * 如果没有使用EBO（VAO没有绑定EBO），可以直接将CPU端的索引数据指针（indices）作为参数传递*
     */
    CHECK_GL_ERROR(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

    shaderTriangle->EndShaderProgram();
    shaderRectangle->EndShaderProgram();
}

bool CreateWindow()
{
    // 初始化窗口
    if (!APP->WindowInit(MAJOR_VERSION, MINOR_VERSION, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE))
    {
        std::cerr << "Failed to initialize GLFW window" << std::endl;
        return false;
    }
    // 设置视口大小及清除颜色
    CHECK_GL_ERROR(glViewport(0, 0, VIEWPORT_WIDTH, VIEWPORT_HEIGHT));
    CHECK_GL_ERROR(glClearColor(0.1f, 0.1f, 0.2f, 1.0f));

    // 事件响应：窗口大小改变
    APP->SetResizeCallback(OnWindowResizeEvent);
    APP->SetKeyCallback(OnKeyEvent);
    // 设置鼠标事件回调
    APP->SetMouseCallback(OnMouseEvent);
    APP->SetCursorCallback(OnCursorEvent);
    APP->SetScrollCallback(OnScrollEvent);

    // 准备三角形数据
    PrepareTriangleData();
    // 变换三角形
    TriangleTransform();
    // 准备四边形数据
    PrepareRectangleData();
    // 准备相机
    PrepareCamera();
    // 准备渲染状态
    PrepareState();

    // 初始化三角形shader对象、纹理对象
    shaderTriangle = std::make_unique<Shader>();
    shaderTriangle->LoadCompileShader(ASSET_DIR "Shader/Vertex.vert", ASSET_DIR "Shader/Fragment.frag");
    textureTriangle = std::make_unique<Texture>();
    textureTriangle->LoadTexture(ASSET_DIR "Texture/Grid.png", 0);

    // 初始化四边形shader对象、纹理对象
    shaderRectangle = std::make_unique<Shader>();
    shaderRectangle->LoadCompileShader(ASSET_DIR "Shader/Vertex.vert", ASSET_DIR "Shader/Fragment.frag");
    textureRectangle = std::make_unique<Texture>();
    textureRectangle->LoadTexture(ASSET_DIR "Texture/Bird.png", 1);

    // 执行渲染循环
    while (APP->WindowUpdate())
    {
        // 更新相机变换矩阵
        cameraControl->Update();
        // 渲染
        Render();
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