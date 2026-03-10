### OpenGL 版本：4.6

---

### 项目结构：
```plaintext
GLRenderer/
├── Asset/            # 资源目录
│   ├── Model/        # 3D模型文件
│   ├── Shader/       # 着色器文件
│   └── Texture/      # 纹理文件
├── Doc/              # 文档目录
│   ├── Screenshot/   # 截图
│   └── *.md          # 文档文件
├── Include/          # 头文件目录
│   ├── Application/  # 应用程序相关
│   ├── Framework/    # 框架核心
│   └── Wrapper/      # 包装类
├── Src/              # 源代码目录
│   ├── Application/  # 应用程序实现
│   ├── Framework/    # 框架实现
│   └── Glad/         # GLAD库
├── ThirdParty/       # 第三方库
├── CMakeLists.txt    # CMake配置文件
└── README.md         # 项目说明
```
---

### 分支
* **[main](https://github.com/chenxu-whisper/GLRenderer/tree/main)**：主线分支，包含最新的功能和修复。
* **[feature](https://github.com/chenxu-whisper/GLRenderer/tree/feature)**：开发分支：开发过程中的新功能和修复：
* **[beginner](https://github.com/chenxu-whisper/GLRenderer/tree/beginner)**：初级分支，包括OpenGL基础知识：
  * 基础功能
    * 窗体创建
    * 上下文创建
    * 渲染循环
    * 事件处理
  * 顶点数据管理
    * 顶点数组对象（VAO）
    * 顶点缓冲对象（VBO）
    * 索引缓冲对象（EBO）
  * 着色器程序（Shader Program）
    * 链接着色器（Linking Shaders）
    * 激活着色器程序（Using Shader Programs）
  * 流程绘制/渲染管线
     * 顶点着色器（Vertex Shader）
     * 片段着色器（Fragment Shader）
     * ~~几何着色器（Geometry Shader）~~
  * 纹理采样
    * 纹理对象（Texture Object）
    * 纹理坐标（Texture Coordinates）
    * 采样器（Sampler）
    * 多级采样（Mipmapping）
  * 数学模块
    * 向量（Vector）
    * 矩阵（Matrix）
    * 变换（Transformation）
    * 模型矩阵（Model Matrix）
    * 视图矩阵（View Matrix）
    * 投影矩阵（Projection Matrix）
      * 正交投影（Orthographic Projection）
      * 透视投影（Perspective Projection）
  * 相机系统（Camera）
     * 游戏相机（Game Camera）
     * 球相机（Sphere Camera）
  * 深度测试（Depth Testing）
    * 深度缓冲区（Depth Buffer）
    * 深度测试函数（Depth Test Function）
* **[intermediate](https://github.com/ByteDance/GLRenderer/tree/intermediate)**：中级分支，包括OpenGL中级知识：

* **[advanced](https://github.com/ByteDance/GLRenderer/tree/advanced)**：高级分支，包括OpenGL高级知识：

---
