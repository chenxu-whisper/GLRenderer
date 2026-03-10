#include "Framework/Geometry.h"

Geometry::Geometry()
{

}

Geometry::~Geometry()
{
    if (mVAO != 0)
       glDeleteVertexArrays(1, &mVAO);
    if (mPosVBO != 0)
        glDeleteBuffers(1, &mPosVBO);
    if (mColorVBO != 0)
        glDeleteBuffers(1, &mColorVBO);
    if (mUvVBO != 0)
        glDeleteBuffers(1, &mUvVBO);
    if (mEBO != 0)
        glDeleteBuffers(1, &mEBO);
}

GLuint Geometry::GetVAO() const { return mVAO; }

GLuint Geometry::GetIndices() const { return mIndices; }

std::shared_ptr<Geometry> Geometry::CreateCube(float length, float width, float height)
{
    auto geometry = std::make_shared<Geometry>();
    geometry->mIndices = 36; // 6个面，每个面6个顶点

    // 位置
    float positions[] =
    {
        // 前
        -length / 2, -width / 2,  height / 2,
        length / 2, -width / 2,  height / 2,
        length / 2,  width / 2,  height / 2,
        -length / 2,  width / 2,  height / 2,
        // 后
        -length / 2, -width / 2, -height / 2,
        length / 2, -width / 2, -height / 2,
        length / 2,  width / 2, -height / 2,
        -length / 2,  width / 2, -height / 2,
        // 左
        -length / 2, -width / 2, -height / 2,
        -length / 2, -width / 2,  height / 2,
        -length / 2,  width / 2,  height / 2,
        -length / 2,  width / 2, -height / 2,
        // 右
        length / 2, -width / 2, -height / 2,
        length / 2, -width / 2,  height / 2,
        length / 2,  width / 2,  height / 2,
        length / 2,  width / 2, -height / 2,
        // 上
        -length / 2,  width / 2,  height / 2,
        length / 2,  width / 2,  height / 2,
        length / 2,  width / 2, -height / 2,
        -length / 2,  width / 2, -height / 2,
        // 下
        -length / 2, -width / 2, -height / 2,
        length / 2, -width / 2, -height / 2,
        length / 2, -width / 2,  height / 2,
        -length / 2, -width / 2,  height / 2,
    };
    // 颜色
    float colors[] =
    {
        // 前 - 红色
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        // 后 - 绿色
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        // 左 - 蓝色
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        // 右 - 黄色
        1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,
        // 上 - 青色
        0.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f,
        // 下 - 品红
        1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 1.0f,
    };
    //  uv
    float uvs[] =
    {
        // 前
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        // 后
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        // 左
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        // 右
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        // 上
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        // 下
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
    };
    // 索引
    GLuint indices[] =
    {
        // 前
        0, 1, 2, 2, 3, 0,
        // 后
        4, 5, 6, 6, 7, 4,
        // 左
        8, 9, 10, 10, 11, 8,
        // 右
        12, 13, 14, 14, 15, 12,
        // 上
        16, 17, 18, 18, 19, 16,
        // 下
        20, 21, 22, 22, 23, 20,
    };

    // 位置 VBO
    glGenBuffers(1, &geometry->mPosVBO);
    glBindBuffer(GL_ARRAY_BUFFER, geometry->mPosVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    // 颜色 VBO
    glGenBuffers(1, &geometry->mColorVBO);
    glBindBuffer(GL_ARRAY_BUFFER, geometry->mColorVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    // UV VBO
    glGenBuffers(1, &geometry->mUvVBO);
    glBindBuffer(GL_ARRAY_BUFFER, geometry->mUvVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);

    // 索引 VBO
    GLuint& mEBO = geometry->mEBO;
    glGenBuffers(1, &mEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // VAO
    glGenVertexArrays(1, &geometry->mVAO);
    glBindVertexArray(geometry->mVAO);

    // 位置属性
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, geometry->mPosVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void *>(nullptr));

    // 颜色属性
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, geometry->mColorVBO);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), static_cast<void *>(nullptr));

    // UV 属性
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, geometry->mUvVBO);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), static_cast<void *>(nullptr));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->mEBO);

    // 解绑VAO
    glBindVertexArray(0);

    return geometry;
}

std::shared_ptr<Geometry> Geometry::CreateSphere(float radius)
{
    auto geometry = std::make_shared<Geometry>();

    std::vector<GLfloat> positions; // 位置
    std::vector<GLfloat> colors; // 颜色
    std::vector<GLfloat> uvs; // uv
    std::vector<GLuint> indices; // 索引

    const int numLatLines = 32; // 纬度线数
    const int numLongLines = 32; // 经度线数

    // 生成球的顶点
    for (int i = 0; i <= numLatLines; i++) // 纬度
    {
        for (int j = 0; j <= numLongLines; j++) // 经度
        {
            // 计算当前点的位置
            float lat = M_PI * i / (float)numLatLines;
            float lon = 2 * M_PI * j / (float)numLongLines;

            // 计算当前点的坐标
            float x = radius * sin(lat) * cos(lon);
            float y = radius * cos(lat);
            float z = radius * sin(lat) * sin(lon);
            // 加入位置
            positions.push_back(x);
            positions.push_back(y);
            positions.push_back(z);

            // 加入颜色
            float r = 0.5f * (1.0f + sin(lat));
            float g = 0.5f * (1.0f + cos(lat));
            float b = 0.5f;
            float a = 1.0f;
            colors.push_back(r);
            colors.push_back(g);
            colors.push_back(b);
            colors.push_back(a);

            // 计算当前点的uv
            float u = (float)j / numLongLines;
            float v = 1.0f - (float)i / numLatLines;

            // 加入uv
            uvs.push_back(u);
            uvs.push_back(v);
        }
    }

    // 生成球的索引
    for (int i = 0; i < numLatLines; i++) // 纬度
    {
        for (int j = 0; j < numLongLines; j++) // 经度
        {
            // 计算当前点的索引
            int p1 = i * (numLongLines + 1) + j; // 当前点
            int p2 = p1 + numLongLines + 1; // 下一个纬度的当前点
            int p3 = p1 + 1; // 下一个经度的当前点
            int p4 = p2 + 1; // 下一个纬度的下一个经度的当前点

            // 加入索引
            // 加入索引，确保正确的三角形绘制顺序（逆时针）
            indices.push_back(p1);
            indices.push_back(p2);
            indices.push_back(p3);

            indices.push_back(p3);
            indices.push_back(p2);
            indices.push_back(p4);
        }
    }

    // 生成VAO
    CHECK_GL_ERROR(glGenVertexArrays(1, &geometry->mVAO));
    CHECK_GL_ERROR(glBindVertexArray(geometry->mVAO));
    // 位置 VBO
    CHECK_GL_ERROR(glGenBuffers(1, &geometry->mPosVBO));
    CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, geometry->mPosVBO));
    CHECK_GL_ERROR(glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(GLfloat), positions.data(), GL_STATIC_DRAW));
    // 颜色 VBO
    CHECK_GL_ERROR(glGenBuffers(1, &geometry->mColorVBO));
    CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, geometry->mColorVBO));
    CHECK_GL_ERROR(glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(GLfloat), colors.data(), GL_STATIC_DRAW));
    // UV VBO
    CHECK_GL_ERROR(glGenBuffers(1, &geometry->mUvVBO));
    CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, geometry->mUvVBO));
    CHECK_GL_ERROR(glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(GLfloat), uvs.data(), GL_STATIC_DRAW));
    // 索引 VBO
    CHECK_GL_ERROR(glGenBuffers(1, &geometry->mEBO));
    CHECK_GL_ERROR(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->mEBO));
    CHECK_GL_ERROR(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW));
    // 位置属性
    CHECK_GL_ERROR(glEnableVertexAttribArray(0));
    CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, geometry->mPosVBO));
    CHECK_GL_ERROR(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void *>(nullptr)));
    // 颜色属性
    CHECK_GL_ERROR(glEnableVertexAttribArray(1));
    CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, geometry->mColorVBO));
    CHECK_GL_ERROR(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), static_cast<void *>(nullptr)));
    // UV 属性
    CHECK_GL_ERROR(glEnableVertexAttribArray(2));
    CHECK_GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, geometry->mUvVBO));
    CHECK_GL_ERROR(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), static_cast<void *>(nullptr)));
    // 绑定EBO到VAO
    CHECK_GL_ERROR(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->mEBO));
    // 解绑VAO
    CHECK_GL_ERROR(glBindVertexArray(0));

    // 索引数量
    geometry->mIndices = indices.size();

    return geometry;
}
