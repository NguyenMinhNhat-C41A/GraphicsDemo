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

    std::pair<float, float> getMousePosition();
    std::pair<float, float> getLastMousePosition();
    std::pair<float, float> getMouseOffset();
    float getMouseSensitivity();

    bool isButtonPressed(int p_sBttn);
    bool isButtonReleased(int p_sBttn);

    bool isShiftPressed();

private:
    IOManager(wolf::App *p_pApp);
    virtual ~IOManager();

    static IOManager *s_pIOManagerInstance;

    static const int NUM_KEYS = GLFW_KEY_LAST - GLFW_KEY_SPACE;
    wolf::App *m_pApp = nullptr;

    bool m_bKeysDown[NUM_KEYS];
    bool m_bKeysDownLast[NUM_KEYS];

    float m_fSpeed = 5.0f;

    std::pair<float, float> m_MousePos = {0.0f, 0.0f};
    std::pair<float, float> m_LastMousePos = {0.0f, 0.0f};
    std::pair<float, float> m_MouseOffset = {0.0f, 0.0f};

    float m_fMouseSensitivity = 0.1f;
};