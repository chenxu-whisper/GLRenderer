# Learn OpenGL(Version 4.6)


> **参考链接**
> * https://learnopengl-cn.readthedocs.io/zh/latest/
> * https://ai.feishu.cn/docx/W6Eod11C2onvCdxa347crqWunPh

---

### 依赖库
* [GLFW](https://www.glfw.org/) : 个专门针对OpenGL的C语言库,它提供了一些渲染物体所需需的最低限度的接口，如创建窗口、处理输入事件等。
* [GLAD](https://glad.dav1d.de/) : 根据不同的OpenGL版本,它提供了不同的函数指针,可以在不同的平台上使用，如在Windows上使用OpenGL 4.5,在macOS上使用OpenGL 4.1等。
* [GLEW](https://glew.sourceforge.net/) : 是一个跨平台的C++库,它提供了OpenGL的扩展功能，如加载OpenGL扩展函数指针等。
* [GLM](https://glm.g-truc.net/0.9.9/index.html) : 是一个OpenGL的数学库,它提供了一些常用的数学操作,如向量、矩阵、四元数等，

---

### 词义解析
#### OpenGL状态机（State Machine）
* **定义**：OpenGL运行环境是一个大的状态机,每一个函数都会改变状态机的状态或者触发其执行某个行为。是一种 “存储当前状态 + 响应输入触发状态转换” 的系统。
* **核心分类**：OpenGL 的状态可分为三大类，覆盖了渲染的全流程：
  * **渲染配置状态**：启用 / 禁用深度测试（`glEnable(GL_DEPTH_TEST)`）、混合模式（`glBlendFunc`）、面剔除（`glCullFace`）等。
  * **资源绑定状态**：当前绑定的顶点数组对象（VAO）、顶点缓冲（VBO）、纹理（`glBindTexture`）、着色器程序（`glUseProgram`）等。
  * **参数配置状态**：视口大小（`glViewport`）、清屏颜色（`glClearColor`）、深度测试函数（`glDepthFunc`）等。
* **工作流程**：以 “渲染一个带纹理的三角形” 为例，状态机的流转逻辑：
  1. **初始化状态**：
     1. 设置清屏颜色：`glClearColor(0.1f, 0.1f, 0.1f, 1.0f)`（状态持久化）。
     2. 启用深度测试：`glEnable(GL_DEPTH_TEST)`（状态持久化）。
     3. 绑定 VAO：`glBindVertexArray(vaoID)`（当前 VAO 状态被激活）。
  2. **绑定资源状态**：
     1. 绑定 VBO 并上传顶点数据：`glBindBuffer(GL_ARRAY_BUFFER, vboID)`（操作依赖当前绑定的 VBO）。
     2. 绑定纹理并设置参数：`glBindTexture(GL_TEXTURE_2D, texID)` → `glTexParameteri(...)`（操作依赖当前绑定的纹理）。
     3. 激活着色器程序：`glUseProgram(shaderID)`（后续绘制使用该程序）。
  3. **执行渲染操作**：
     1. 清屏：`glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)`（依赖`glClearColor`状态）。
     2. 绘制三角形：`glDrawArrays(GL_TRIANGLES, 0, 3)`（依赖当前绑定的 VAO、着色器程序、纹理等状态）。
  4. **状态切换 / 重置**：
     1. 解绑纹理：`glBindTexture(GL_TEXTURE_2D, 0)`（重置 “当前纹理” 状态）。
     2. 停用着色器程序：`glUseProgram(0)`（重置 “当前程序” 状态）。

#### OpenGL双缓冲（Double Buffer）
* **定义**：在后台缓冲完成完整画面的绘制后，通过缓冲交换将后缓冲的内容一次性替换到前缓冲，避免用户看到 “半完成的绘制过程”，从而消除闪烁。
  * 前缓冲（Front Buffer）：当前正在显示器上显示的缓冲，用户看到的画面来自此缓冲。
  * 后缓冲（Back Buffer）：后台用于绘制的缓冲，所有渲染命令（如`glDrawArrays`）都会先输出到后缓冲。
