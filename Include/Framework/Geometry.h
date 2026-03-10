#ifndef GLRENDERER_GEOMETRY_H
#define GLRENDERER_GEOMETRY_H

#include "Core.h"

class Geometry
{
public:
    Geometry();
    ~Geometry();

    GLuint GetVAO() const;
    GLuint GetIndices() const;

    static std::shared_ptr<Geometry> CreateCube(float length, float width, float height);
    static std::shared_ptr<Geometry> CreateSphere(float radius);

private:
    GLuint mVAO = 0; // 顶点数组对象 Vertex Array Object
    GLuint mPosVBO = 0; // 顶点缓冲对象 Vertex Buffer Object
    GLuint mColorVBO = 0; // 颜色缓冲对象 Color Buffer Object
    GLuint mUvVBO = 0; // 纹理坐标缓冲对象 Texture Coordinate Buffer Object
    GLuint mEBO = 0; // 元素缓冲对象 Element Buffer Object
    GLuint mIndices = 0; // 索引数量 Index count
};

#endif //GLRENDERER_GEOMETRY_H