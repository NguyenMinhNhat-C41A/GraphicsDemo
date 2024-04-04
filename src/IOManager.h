#pragma once
#include "../wolf/wolf.h"
#include <iostream>
#include "glfwKeyMap.h"
class IOManager
{
public:
    static void createInstance(wolf::App *p_pApp);
    static void destroyInstance();
    static IOManager *Instance();

    virtual void update(float p_fDelta);
    glm::vec2 getMouseOffset();
    float getMouseSensitivity();

    bool isButtonPressed(int p_sBttn);
    bool isButtonReleased(int p_sBttn);

    bool isShiftPressed();

private:
    IOManager(wolf::App *p_pApp);
    virtual ~IOManager();

    static IOManager *s_pIOManagerInstance;

    wolf::App *m_pApp = nullptr;

    bool m_bKeysDown[256];
    bool m_bKeysDownLast[256];

    bool isUpdateNeeded = false;

    float m_fSpeed = 5.0f;

    glm::vec2 m_vMouseOffset = glm::vec2(0.0f);
    glm::vec2 m_vLastMousePos = glm::vec2(0.0f);
    float m_fMouseSensitivity = 0.01f;
};