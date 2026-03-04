
#ifndef GLRENDERER_CAMERACONTROL_H
#define GLRENDERER_CAMERACONTROL_H

#include <map>

#include "Core.h"
#include "Application/Camera/Camera.h"

class CameraControl
{
public:
    CameraControl();
    virtual ~CameraControl();

    /*
    * @brief 处理鼠标输入
    * @param button 鼠标按钮ID
    * @param action 鼠标按钮动作（按下/释放）
    * @param xpos 鼠标在窗口中的X坐标
    * @param ypos 鼠标在窗口中的Y坐标
    */
    virtual void OnMouse(int button, int action, double xpos, double ypos);
    /*
    * @brief 处理鼠标移动输入
    * @param xpos 鼠标在窗口中的X坐标
    * @param ypos 鼠标在窗口中的Y坐标
    */
    virtual void OnCursor(double xpos, double ypos);
    /*
    * @brief 处理鼠标滚动输入
    * @param xoffset 鼠标水平滚动偏移量
    * @param yoffset 鼠标垂直滚动偏移量
    */
    virtual void OnScroll(double xoffset, double yoffset);
    /*
    * @brief 处理键盘输入
    * @param key 按键ID
    * @param action 按键动作（按下/释放）
    * @param mods 按键修饰符（Shift/Ctrl/Alt）
    */
    virtual void OnKey(int key, int action, int mods);

    // 更新相机状态
    virtual void Update();

    void SetCamera(Camera* camera);
    void SetSensitivity(float sensitivity);
    void SetScaleSpeed(float scaleSpeed);

protected:
    // 关联的相机
    Camera* mCamera = nullptr;
    // 鼠标状态
    bool mLeftMouseDown = false;
    bool mRightMouseDown = false;
    bool mMiddleMouseDown = false;
    // 鼠标位置
    float mCurrentX = 0.0f;
    float mCurrentY = 0.0f;
    // 鼠标灵敏度
    float mSensitivity = 0.2f;
    // 相机缩放速度
    float mScaleSpeed = 0.1f;
    // 按键映射表
    std::map<uint8_t, bool> mKeysMap;
};


#endif //GLRENDERER_CAMERACONTROL_H