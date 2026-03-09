#include "Application/Camera/PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(float fovy, float aspect, float near, float far)
    : mFovy(fovy), mAspect(aspect), mNear(near), mFar(far)
{

}

PerspectiveCamera::~PerspectiveCamera()
{

}

glm::mat4 PerspectiveCamera::GetProjectionMatrix() const
{
    return glm::perspective(glm::radians(mFovy), mAspect, mNear, mFar);
}

void PerspectiveCamera::Scale(float deltaScale)
{
    // 根据相机的前端向量进行缩放
    auto front = glm::cross(mUp, mRight);
    mPosition += front * deltaScale;
}
