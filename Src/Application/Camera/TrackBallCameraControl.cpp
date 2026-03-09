#include "Application/Camera/TrackBallCameraControl.h"

TrackBallCameraControl::TrackBallCameraControl()
{

}

TrackBallCameraControl::~TrackBallCameraControl()
{

}

void TrackBallCameraControl::OnCursor(double xpos, double ypos)
{
    if (mLeftMouseDown)
    {
        float deltaX = (xpos -mCurrentX) * mSensitivity;
        float deltaY = (ypos -mCurrentY) * mSensitivity;

        Yaw(-deltaX);
        Pitch(-deltaY);
    }
    else if (mMiddleMouseDown)
    {
        float deltaX = (xpos -mCurrentX) * mMoveSpeed;
        float deltaY = (ypos -mCurrentY) * mMoveSpeed;

        mCamera->mPosition -= mCamera->mRight * deltaX;
        mCamera->mPosition += mCamera->mUp * deltaY;
    }

    mCurrentX = xpos;
    mCurrentY = ypos;
}

void TrackBallCameraControl::OnScroll(double xoffset, double yoffset)
{
    // 处理鼠标滚动事件
    mCamera->Scale(yoffset * mScaleSpeed);
}

void TrackBallCameraControl::Yaw(float angle)
{
    auto mat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), mCamera->mUp);

    mCamera->mRight = glm::vec3(mat * glm::vec4(mCamera->mRight, 0.0f));
    mCamera->mPosition = glm::vec3(mat * glm::vec4(mCamera->mPosition, 0.0f));
}

void TrackBallCameraControl::Pitch(float angle)
{
    auto mat = glm::rotate(glm::mat4(1.0f), glm::radians(angle), mCamera->mRight);

    mCamera->mUp = glm::vec3(mat * glm::vec4(mCamera->mUp, 0.0f));
    mCamera->mPosition = glm::vec3(mat * glm::vec4(mCamera->mPosition, 0.0f));
}
