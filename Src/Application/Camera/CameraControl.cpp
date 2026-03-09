#include "Application/Camera/CameraControl.h"

CameraControl::CameraControl()
{

}

CameraControl::~CameraControl()
{

}

void CameraControl::OnMouse(int button, int action, double xpos, double ypos)
{
    // 处理鼠标按下事件
    bool isPressed = action == GLFW_PRESS ? true : false;

    // 记录当前鼠标位置
    if (isPressed)
    {
        mCurrentX = xpos;
        mCurrentY = ypos;
    }

    // 处理鼠标按钮事件
    switch (button)
    {
        case GLFW_MOUSE_BUTTON_LEFT:
            mLeftMouseDown = isPressed;
            break;
        case GLFW_MOUSE_BUTTON_RIGHT:
            mRightMouseDown = isPressed;
            break;
        case GLFW_MOUSE_BUTTON_MIDDLE:
            mMiddleMouseDown = isPressed;
            break;
    }
}

void CameraControl::OnCursor(double xpos, double ypos)
{

}

void CameraControl::OnScroll(double xoffset, double yoffset)
{

}

void CameraControl::OnKey(int key, int action, int mods)
{
    // 忽略重复按键事件
    if (action == GLFW_REPEAT)
        return;

    // 处理鼠标按下事件
    bool isPressed = action == GLFW_PRESS ? true : false;

    // 记录当前按键状态
    mKeysMap[key] = isPressed;
}

void CameraControl::Update()
{

}

void CameraControl::SetCamera(Camera *camera)
{
    this->mCamera = camera;
}

void CameraControl::SetSensitivity(float sensitivity)
{
    this->mSensitivity = sensitivity;
}

void CameraControl::SetScaleSpeed(float scaleSpeed)
{
    this->mScaleSpeed = scaleSpeed;
}
