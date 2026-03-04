//
// Created by Admin on 2026/2/25.
//

#ifndef GLRENDERER_PERSPECTIVECAMERA_H
#define GLRENDERER_PERSPECTIVECAMERA_H

#include "../Core.h"
#include "Application/Camera/Camera.h"


class PerspectiveCamera : public Camera
{
public:
    PerspectiveCamera(float fovy, float aspect, float near, float far);
    ~PerspectiveCamera() override;

    glm::mat4 GetProjectionMatrix() const override;
    // 缩放相机位置
    void Scale(float deltaScale) override;

private:
    float mFovy = 45.0f;
    float mAspect = 16.0f / 9.0f;
    float mNear = 0.01f;
    float mFar = 1000.0f;
};


#endif //GLRENDERER_PERSPECTIVECAMERA_H