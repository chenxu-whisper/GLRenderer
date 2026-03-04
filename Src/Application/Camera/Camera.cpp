#include "Application/Camera/Camera.h"

Camera::Camera() {}
Camera::~Camera() {}

glm::mat4 Camera::GetViewMatrix() const
{
    glm::vec3 front = glm::cross(mUp, mRight);
    glm::vec3 center = mPosition + front;

    return glm::lookAt(mPosition, center, mUp);
}

glm::mat4 Camera::GetProjectionMatrix() const
{
    return glm::identity<glm::mat4>(); // 单位矩阵
}

void Camera::Scale(float deltaScale)
{

}
