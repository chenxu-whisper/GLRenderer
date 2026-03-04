#include "Application/Camera/OrthographicCamera.h"

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float near, float far)
    : mLeft(left), mRight(right), mBottom(bottom), mTop(top), mNear(near), mFar(far)
{

}

OrthographicCamera::~OrthographicCamera()
{

}

glm::mat4 OrthographicCamera::GetProjectionMatrix() const
{
    // 根据相机的缩放因子进行缩放
    float cameraScale = pow(2.0f, mScale);
    return glm::ortho(mLeft * cameraScale, mRight * cameraScale, mBottom * cameraScale, mTop * cameraScale, mNear, mFar);
}

void OrthographicCamera::Scale(float deltaScale)
{
    // 根据相机的缩放因子进行缩放
    mScale += deltaScale;
}