#ifndef GLRENDERER_TEXTURE_H
#define GLRENDERER_TEXTURE_H

#define STB_IMAGE_IMPLEMENTATION // 必须在包含stb_image.h之前定义
#include "Core.h"

class Texture
{
public:
    Texture();
    ~Texture();

    /*
     * @brief 加载纹理对象
     * @param filePath: 纹理文件路径
     * @param textureUnit: 要绑定的纹理单元，这里是textureTriangle->GetTextureUnit()
     */
    void LoadTexture(const std::string& filePath, unsigned int textureUnit);

    /*
     * @brief 获取纹理对象的ID
     * @return 纹理对象的ID
     */
    GLuint GetTextureID() const;
    /*
     * @brief 获取纹理对象的绑定纹理单元
     * @return 纹理对象的绑定纹理单元
     */
    unsigned int GetTextureUnit() const;

private:
    /*
     * @brief 纹理对象的ID
     */
    GLuint mTextureID = 0;
    /*
     * @brief 纹理对象的绑定纹理单元
     */
    unsigned int mTextureUnit = 0;
    /*
     * @brief 纹理对象的宽度
     */
    int mWidth = 0;
    /*
     * @brief 纹理对象的高度
     */
    int mHeight = 0;
    /*
     * @brief 纹理对象的通道数
     */
    int mChannels = 0;
};


#endif //GLRENDERER_TEXTURE_H