#include "Framework/Texture.h"

Texture::Texture() = default;

Texture::~Texture()
{
    // 删除纹理对象
    if (mTextureID != 0)
        glDeleteTextures(1, &mTextureID);
}

void Texture::LoadTexture(const std::string& filePath, unsigned int textureUnit)
{
    // 初始化纹理单元
    mTextureUnit = textureUnit;

    // 翻转图像垂直方向
    stbi_set_flip_vertically_on_load(true);
    /* 加载图像数据到内存
     * @param filename: 图像文件路径
     * @param x: 指向int的指针，用于存储图像宽度，这里是width
     * @param y: 指向int的指针，用于存储图像高度，这里是height
     * @param channels: 指向int的指针，用于存储图像通道数，这里是channels
     * @param desiredChannels: 期望的通道数，这里是0，即自动根据图像文件确定通道数
     * @return: 指向图像数据的指针，这里是imageData
     */
    uint8_t* imageData = stbi_load(filePath.c_str(), &mWidth, &mHeight, &mChannels, 0);
    if (!imageData)
    {
        std::cerr << "Failed to load image: " << stbi_failure_reason() << std::endl;
        return;
    }

    /*
     * @brief 生成纹理对象
     * @param n: 要生成的缓冲区对象数量，这里是1
     * @param arrays: 指向GLuint数组的指针，用于存储生成的缓冲区对象ID
     */
    glGenTextures(1, &mTextureID);
    /*
     * @brief 激活纹理单元0，将后续的纹理操作应用到该纹理单元
     * @param textureUnit: 要激活的纹理单元，这里是GL_TEXTURE0
     */
    glActiveTexture(GL_TEXTURE0 + mTextureUnit);
    /*
     * @brief 绑定纹理对象到当前OpenGL状态机的当前纹理插槽
     * @param target: 纹理目标，这里是GL_TEXTURE_2D，即2D纹理
     * @param texture: 要绑定的纹理对象ID，这里是mTextureID
     */
    glBindTexture(GL_TEXTURE_2D, mTextureID);

    // 根据通道数设置格式
    int format;
    if (mChannels == 1)
        format = GL_RED;
    else if (mChannels == 3)
        format = GL_RGB;
    else if (mChannels == 4)
        format = GL_RGBA;
    else
    {
        std::cerr << "Unsupported image channels: " << mChannels << std::endl;
        stbi_image_free(imageData);

        return;
    }

    /*
     * @brief 加载图像数据到纹理对象，开辟显存
     * @param target: 纹理目标，这里是GL_TEXTURE_2D，即2D纹理
     * @param level: 纹理级别（mipmap级别），这里是0，即基本级别
     * @param internalFormat: 内部格式，这里是GL_RGBA，即4通道8位无符号整数
     * @param width: 纹理宽度，这里是width
     * @param height: 纹理高度，这里是height
     * @param border: 边框宽度，这里是0
     * @param format: 数据格式，这里是GL_RGBA，即4通道8位无符号整数
     * @param type: 数据类型，这里是GL_UNSIGNED_BYTE，每个组件占用1个字节
     * @param data: 指向图像数据的指针，这里是imageData
     */
    glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, imageData);

    /* 生成MIPMAP链
    * @param target: 纹理目标，这里是GL_TEXTURE_2D，即2D纹理
    */
    glGenerateMipmap(GL_TEXTURE_2D);
    /*
     * @brief 设置缩小过滤方式
     * @param target: 纹理目标，这里是GL_TEXTURE_2D，即2D纹理
     * @param pname: 纹理参数名称，这里是GL_TEXTURE_MIN_FILTER，即 minification filter
     * @param param: 纹理参数值，GL_LINEAR_MIPMAP_LINEAR，即线性过滤（MIPMAP级别）
     */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    /*
     * @brief 设置放大过滤方式
     * @param target: 纹理目标，这里是GL_TEXTURE_2D，即2D纹理
     * @param pname: 纹理参数名称，这里是GL_TEXTURE_MAG_FILTER，即 magnification filter
     * @param param: 纹理参数值，GL_LINEAR，即线性过滤
     */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    /*
     * @brief 设置 T 轴（V 坐标）环绕方式
     * @param target: 纹理目标，这里是GL_TEXTURE_2D，即2D纹理
     * @param pname: 纹理参数名称，这里是GL_TEXTURE_WRAP_T，即 texture wrap parameter for the T coordinate
     * @param param: 纹理参数值，这里是GL_REPEAT，即重复环绕
     */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // T / V
    /*
     * @brief 设置 S 轴（U 坐标）环绕方式
     * @param target: 纹理目标，这里是GL_TEXTURE_2D，即2D纹理
     * @param pname: 纹理参数名称，这里是GL_TEXTURE_WRAP_S，即 texture wrap parameter for the S coordinate
     * @param param: 纹理参数值，这里是GL_REPEAT，即重复环绕
     */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // U / S

    // 释放图像数据内存
    stbi_image_free(imageData);
}

GLuint Texture::GetTextureID() const { return mTextureID; }

unsigned int Texture::GetTextureUnit() const { return mTextureUnit; }