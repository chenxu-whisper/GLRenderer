#ifndef GLRENDERER_GAMECAMERACONTROL_H
#define GLRENDERER_GAMECAMERACONTROL_H

#include "Application/Camera/CameraControl.h"

class GameCameraControl : public CameraControl
{
public:
    GameCameraControl();
    ~GameCameraControl() override;

    // 处理鼠标位置变化事件
    void OnCursor(double xpos, double ypos) override;
    void Update() override;

private:
    void Yaw(float angle);
    void Pitch(float angle);

private:
    // 相机旋转角度
    float mYaw = 0.0f;
    float mPitch = 0.0f;

    // 相机移动速度
    float mSpeed = 0.01f;
};


#endif //GLRENDERER_GAMECAMERACONTROL_H