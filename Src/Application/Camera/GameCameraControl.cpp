#include "Application/Camera/GameCameraControl.h"

#include <algorithm>

GameCameraControl::GameCameraControl()
{

}

GameCameraControl::~GameCameraControl()
{

}

void GameCameraControl::OnCursor(double xpos, double ypos)
{
    if (mRightMouseDown)
    {
        // 计算水平垂直旋转角度
        float deltaX = (xpos - mCurrentX) * mSensitivity;
        float deltaY = (ypos - mCurrentY) * mSensitivity;

        Yaw(deltaX);
        Pitch(deltaY);
    }

    // 更新当前鼠标位置
    mCurrentX = xpos;
    mCurrentY = ypos;
}

void GameCameraControl::Update()
{
    auto direction = glm::vec3(0.0f, 0.0f, 0.0f);

    auto front = glm::cross(mCamera->mRight, mCamera->mUp);
    auto right = mCamera->mRight;

    if (mKeysMap[GLFW_KEY_W])
    {
        direction += front;
    }
    if (mKeysMap[GLFW_KEY_S])
    {
        direction -= front;
    }
    if (mKeysMap[GLFW_KEY_A])
    {
        direction -= right;
    }
    if (mKeysMap[GLFW_KEY_D])
    {
        direction += right;
    }

    if (glm::length(direction) != 0.0f)
    {
        direction = glm::normalize(direction);
        mCamera->mPosition -= direction * mSpeed;
    }
}

void GameCameraControl::Yaw(float angle)
{
    // 更新水平旋转角度
    mYaw += angle;
    if (mYaw > 89.0f || mYaw < -89.0f)
    {
        mYaw -= angle;
        return;
    }

    glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    auto mat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), worldUp);
    mCamera->mRight = glm::vec3(mat * glm::vec4(mCamera->mRight, 0.0f));
    mCamera->mUp = glm::vec3(mat * glm::vec4(mCamera->mUp, 0.0f));
}

void GameCameraControl::Pitch(float angle)
{
    mPitch += angle;
    if (mPitch > 89.0f || mPitch < -89.0f)
    {
        mPitch -= angle;
        return;
    }



    auto mat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), mCamera->mRight);
    mCamera->mUp = glm::vec3(mat * glm::vec4(mCamera->mUp, 0.0f));
}
