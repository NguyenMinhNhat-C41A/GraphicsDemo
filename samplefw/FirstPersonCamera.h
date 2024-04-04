#pragma once
#include <iostream>
#include "../wolf/wolf.h"
#include "plane.h"

class FirstPersonCamera
{
public:
    struct Frustum
    {
        Plane leftPlane;
        Plane rightPlane;

        Plane topPlane;
        Plane bottomPlane;

        Plane nearPlane;
        Plane farPlane;
    };
    FirstPersonCamera(wolf::App *pApp);
    virtual ~FirstPersonCamera();
    glm::mat4 getViewMatrix();
    glm::mat4 getProjMatrix();
    void update(const float dt);

    Frustum getFrustum();

private:
    glm::vec3 camPosition = glm::vec3(0.0f, 0.0f, 00.0f);
    glm::vec3 camViewFront = glm::vec3(-1.0f, 0.0f, 0.0f);
    glm::vec3 camMoveFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 camUp = glm::vec3(0.0f, 1.0f, 0.0f);

    float pitch = 0.0f;
    const float MAX_PITCH = 89.0f;

    float yaw = -90.0f;

    float mouseSensitivity = 0.1f;

    float camSpeed = 1.0f;
    std::vector<float> camSpeeds = {4.0f, 8.0f, 16.0f, 32.0f, 64.0f};
    unsigned int camSpeedIndex = 2;
    float camFlySpeed = 1.0f;
    float camTankRotSpeed = 60.0f;
    float camAcceleration = 0.0f;

    float m_fov = glm::radians(60.0f);
    float m_near = 0.1f;
    float m_far = 3000.0f;

    bool m_bIsRunning = true;
    bool m_bIsRDown = false;

    bool m_bIsWheelchairMode = false;
    bool m_bIsFDown = false;

    glm::vec2 lastMousePos = glm::vec2(0.0f, 0.0f);
    wolf::App *m_pApp = nullptr;
};