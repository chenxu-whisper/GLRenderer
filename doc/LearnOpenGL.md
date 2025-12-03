# Learn OpenGL

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
#### OpenGL上下文（Context）
* **定义**：OpenGL上下文是一个对象,它包含了OpenGL运行环境的所有状态信息,如当前绑定的顶点数组对象、当前使用的着色器程序、当前设置的视口大小等。
* **作用**：OpenGL上下文是OpenGL运行环境的核心,它负责管理OpenGL的状态,并根据状态执行渲染操作。：是 OpenGL的“物理载体”，解决“在哪里运行”的问题（提供资源和环境）。
* **本质**：一块独立的、包含 OpenGL 所有运行所需资源的内存区域，是连接 CPU 代码与 GPU 的 “桥梁”。

#### OpenGL状态机（State Machine）
* **定义**：OpenGL运行环境是一个大的状态机,每一个函数都会改变状态机的状态或者触发其执行某个行为。是一种 “存储当前状态 + 响应输入触发状态转换” 的系统。
* * **作用**：是OpenGL的“逻辑规则”，解决“如何运行”的问题（操作依赖当前状态）。
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
    4. **状态切换/重置**：
        1. 解绑纹理：`glBindTexture(GL_TEXTURE_2D, 0)`（重置 “当前纹理” 状态）。
        2. 停用着色器程序：`glUseProgram(0)`（重置 “当前程序” 状态）。

#### OpenGL双缓冲（Double Buffer）
* **定义**：在后台缓冲完成完整画面的绘制后，通过缓冲交换将后缓冲的内容一次性替换到前缓冲，避免用户看到 “半完成的绘制过程”，从而消除闪烁。
    * 前缓冲（Front Buffer）：当前正在显示器上显示的缓冲，用户看到的画面来自此缓冲。
    * 后缓冲（Back Buffer）：后台用于绘制的缓冲，所有渲染命令（如`glDrawArrays`）都会先输出到后缓冲。

#### VBO（Vertex Buffer Object，顶点缓冲对象）
* **作用**：用于存储顶点数据的缓冲对象。它将顶点数据（坐标、颜色、纹理坐标、法线等）从CPU内存转移到GPU显存, 避免每次绘制时重复传输数据，大幅提升渲染效率。在C++中表现为一个unsigned int类型，为GPU端内存对象的一个ID编号。
* **工作流程**：
    1. **创建VBO**：调用`glGenBuffers`生成一个VBO ID（这时还没有分配显存空间, 只是在CPU端创建了一个ID）。
    2. **绑定VBO**：调用`glBindBuffer(GL_ARRAY_BUFFER, vboID)`将VBO绑定到`GL_ARRAY_BUFFER`目标上。
    3. **上传数据**：调用`glBufferData(GL_ARRAY_BUFFER, size, data, usage)`将顶点数据上传到VBO中。
    4. **配置顶点属性指针**：调用`glVertexAttribPointer(index, size, type, normalized, stride, offset)`配置顶点属性指针, 告诉OpenGL如何从VBO中读取数据。
    5. **启用顶点属性数组**：调用`glEnableVertexAttribArray(index)`启用顶点属性数组, 使OpenGL知道从VBO中读取数据。

### VAO（Vertex Array Object，顶点数组对象）
* **作用**：用于存储顶点属性配置的缓冲对象。它将顶点属性（如坐标、颜色、纹理坐标、法线等）的配置信息存储在GPU显存中, 避免每次绘制时重复配置顶点属性指针。在C++中表现为一个unsigned int类型，为GPU端内存对象的一个ID编号。
* **工作流程**：
    1. **创建VAO**：调用`glGenVertexArrays`生成一个VAO ID（这时还没有分配显存空间, 只是在CPU端创建了一个ID）。
    2. **绑定VAO**：调用`glBindVertexArray(vaoID)`将VAO绑定到当前上下文。
    3. **配置顶点属性指针**：调用`glVertexAttribPointer(index, size, type, normalized, stride, offset)`配置顶点属性指针, 告诉OpenGL如何从VBO中读取数据。
    4. **启用顶点属性数组**：调用`glEnableVertexAttribArray(index)`启用顶点属性数组, 使OpenGL知道从VBO中读取数据。
* **layout(location = n)**：在顶点着色器中, 使用`layout(location = n)`指定顶点属性的索引, 与`glVertexAttribPointer(index, ...)`中的`index`对应。
    * 如`layout(location = 0)`指定了顶点坐标的索引为0, 则在`glVertexAttribPointer(0, ...)`中也需要指定索引为0。
    * 如`layout(location = 1)`指定了颜色的索引为1, 则在`glVertexAttribPointer(1, ...)`中也需要指定索引为1。

### EBO（Element Buffer Object，索引缓冲对象）
* **作用**：用于存储索引数据的缓冲对象。复用顶点数据，解决`glDrawArrays`中“重复存储相同顶点”的冗余问题，大幅节省GPU显存和数据传输带宽。在C++中表现为一个unsigned int类型，为GPU端内存对象的一个ID编号。
* **工作流程**：
    1. **创建EBO**：调用`glGenBuffers`生成一个EBO ID（这时还没有分配显存空间, 只是在CPU端创建了一个ID）。
    2. **绑定EBO**：调用`glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID)`将EBO绑定到`GL_ELEMENT_ARRAY_BUFFER`目标上。
    3. **上传数据**：调用`glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage)`将索引数据上传到EBO中。
    4. **绘制元素**：调用`glDrawElements(mode, count, type, offset)`使用EBO中的索引数据绘制元素。
* **EBO与VAO的特殊关联**：只有在VAO绑定状态下的EBO绑定才会被VAO永久记录
    1. **状态记录机制不同**：VAO会永久记录当前绑定的EBO状态，当VAO被绑定时，当前绑定的EBO会被存储到VAO的状态中，这种记录是单向的：EBO的绑定影响VAO，但VAO的解绑不会自动解绑EBO
    2. **解绑VAO时的行为**：解绑VAO只会断开当前上下文与该VAO的连接，但EBO与VAO之间的关联关系已经被记录在VAO内部，解绑VAO不会自动解绑EBO。
    3. **不应该解绑EBO**：解解绑这会导致VAO记录一个无效的EBO绑定（0）, 后续绘制时会使用默认的EBO（0）, 导致绘制错误。

<img src="doc/screenshot/vertex_array_objects_ebo.png" alt="vertex_array_objects_ebo" width="400" height="300">
<div style="display: flex; justify-content: flex-start; align-items: center; gap: 10px;">
  <img src="doc/screenshot/流程与绑定时序图.png" alt="描述2" style="width: 360px; height: 1080px;" />
  <img src="doc/screenshot/组件层级关联结构图.png" alt="描述3" style="width: 1640px; height: 1080px;" />
</div>

### NDC（Normalized Device Coordinates，归一化设备坐标）
* **作用**：是OpenGL渲染管线中的一个坐标系统, 用于将顶点坐标从裁剪空间映射到屏幕空间。
* **范围**：NDC坐标的范围是[-1, 1]，超出此范围的顶点将被裁剪掉。Y轴正方向为向上，(0, 0)坐标是这个图像的中心。
* **计算**：NDC坐标的计算过程如下：
    1. 将顶点坐标的每个分量除以其w分量（透视除法）。
    2. 将结果的x、y、z分量分别映射到[-1, 1]的范围，如顶点坐标为(2, 3, 4)，则NDC坐标为(2/4, 3/4, 4/4) = (0.5, 0.75, 1.0)。
* **工作流程**：
    1. **顶点着色器**：在顶点着色器中, 输入的顶点坐标会被自动转换为NDC坐标。
    2. **光栅化**：在光栅化阶段, NDC坐标会被映射到屏幕空间坐标。
    3. **片段着色器**：在片段着色器中, 输入的屏幕空间坐标会被自动转换为归一化设备坐标。

### Shader（着色器）
* **作用**：用于在GPU上执行渲染操作的程序。它可以是顶点着色器（Vertex Shader）、片段着色器（Fragment Shader）或几何着色器（Geometry Shader）等。
* **工作流程**：
    1. **编写着色器代码**：使用GLSL（OpenGL Shading Language）编写着色器代码, 实现所需的渲染效果。
    2. **创建着色器对象**：调用`glCreateShader`顶点、片元着色器对象。
    3. **着色器代码附加到着色器对象上**： 调用`glShaderSource`把顶点、片元着色器源码附加到着色器对象上。
    4. **编译着色器**：调用`glCompileShader`编译着色器代码, 生成可执行的着色器对象。
    5. **创建着色器程序**：调用`glCreateProgram`创建一个着色器程序对象。
    6. **Attach着色器**：调用`glAttachShader`将编译好的着色器对象Attach到着色器程序中。
    7. **Link着色器程序**：调用`glLinkProgram`将Attach的着色器对象链接到着色器程序中, 生成可执行的着色器程序。
    8. **使用着色器程序**：调用`glUseProgram`使用着色器程序, 后续的渲染操作将使用该程序。
