#ifndef GLRENDERER_ORTHOGRAPHICCAMERA_H
#define GLRENDERER_ORTHOGRAPHICCAMERA_H

#include "../Core.h"
#include "Application/Camera/Camera.h"


class OrthographicCamera : public Camera
{
public:
    OrthographicCamera(float left, float right, float bottom, float top, float near, float far);
    ~OrthographicCamera() override;

    glm::mat4 GetProjectionMatrix() const override;
    // 缩放相机位置
    void Scale(float deltaScale) override;

private:
    float mLeft = -1.0f;
    float mRight = 1.0f;
    float mBottom = -1.0f;
    float mTop = 1.0f;
    float mNear = 0.0f;
    float mFar = 2.0f;

    float mScale = 0.0f;
};


#endif //GLRENDERER_ORTHOGRAPHICCAMERA_H