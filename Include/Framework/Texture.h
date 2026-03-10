#ifndef GLRENDERER_TEXTURE_H
#define GLRENDERER_TEXTURE_H

#define STB_IMAGE_IMPLEMENTATION // 必须在包含stb_image.h之前定义
#include "Core.h"

class Texture
{
public:
    Texture();
    ~Texture();

    void LoadTexture(const std::string& filePath, unsigned int textureUnit);

    // 获取纹理ID
    GLuint GetTextureID() const;
    // 获取纹理单元
    unsigned int GetTextureUnit() const;

private:
    GLuint mTextureID = 0;
    unsigned int mTextureUnit = 0;
    int mWidth = 0;
    int mHeight = 0;
    int mChannels = 0;
};


#endif //GLRENDERER_TEXTURE_H