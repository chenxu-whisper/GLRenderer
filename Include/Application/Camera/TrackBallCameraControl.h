#ifndef GLRENDERER_TRACKBALLCAMERACONTROL_H
#define GLRENDERER_TRACKBALLCAMERACONTROL_H

#include "../Core.h"
#include "Application/Camera/CameraControl.h"

class TrackBallCameraControl : public CameraControl
{
public:
    TrackBallCameraControl();
    ~TrackBallCameraControl() override;

    // 处理鼠标位置变化事件
    void OnCursor(double xpos, double ypos) override;
    // 处理鼠标滚动事件
    void OnScroll(double xoffset, double yoffset) override;

private:
    // 偏航角（水平旋转）
    void Yaw(float angle);
    // 俯仰角（垂直旋转）
    void Pitch(float angle);

private:
    float mMoveSpeed = 0.01f;
};


#endif //GLRENDERER_TRACKBALLCAMERACONTROL_H