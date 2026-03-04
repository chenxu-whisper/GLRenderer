#ifndef GLRENDERER_CAMERA_H
#define GLRENDERER_CAMERA_H

#include "../Core.h"

class Camera
{
public:
    Camera();
    virtual ~Camera();

    glm::mat4 GetViewMatrix() const;
    virtual glm::mat4 GetProjectionMatrix() const;
    virtual void Scale(float deltaScale);

public:
    glm::vec3 mPosition = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::vec3 mUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 mRight = glm::vec3(1.0f, 0.0f, 0.0f);
};


#endif //GLRENDERER_CAMERA_H
