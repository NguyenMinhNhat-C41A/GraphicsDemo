#include "IOManager.h"

IOManager *IOManager::s_pIOManagerInstance = nullptr;

//--------------------------------------------------------------------------------
//
// PUBLIC METHODS
//
//--------------------------------------------------------------------------------

void IOManager::createInstance(wolf::App *p_pApp)
{
    assert(s_pIOManagerInstance == nullptr);
    s_pIOManagerInstance = new IOManager(p_pApp);
}

void IOManager::destroyInstance()
{
    assert(s_pIOManagerInstance != nullptr);
    delete s_pIOManagerInstance;
    s_pIOManagerInstance = nullptr;
}

IOManager *IOManager::Instance()
{
    return IOManager::s_pIOManagerInstance;
}

void IOManager::update(float p_fDelta)
{
    double xpos, ypos;
    glfwGetCursorPos(this->m_pApp->getWindow(), &xpos, &ypos);
    this->m_vMouseOffset = glm::vec2(xpos - this->m_vLastMousePos.x, ypos - this->m_vLastMousePos.y);
    this->m_vLastMousePos = glm::vec2(xpos, ypos);

    for (int i = 0; i < NUM_KEYS; ++i)
    {
        // std::cout << "i: " << i << std::endl;
        m_bKeysDownLast[i] = m_bKeysDown[i];

        m_bKeysDown[i] = glfwGetKey(this->m_pApp->getWindow(), GLFW_KEY_SPACE + i) == GLFW_PRESS;
    }
}

glm::vec2 IOManager::getMouseOffset()
{
    return this->m_vMouseOffset;
}

float IOManager::getMouseSensitivity()
{
    return this->m_fMouseSensitivity;
}

bool IOManager::isButtonPressed(int p_sBttn)
{
    p_sBttn -= GLFW_KEY_SPACE;
    return m_bKeysDown[p_sBttn];
}

bool IOManager::isButtonReleased(int p_sBttn)
{
    p_sBttn -= GLFW_KEY_SPACE;
    return (!m_bKeysDown[p_sBttn] && m_bKeysDownLast[p_sBttn]);
}

bool IOManager::isShiftPressed()
{

    return glfwGetKey(this->m_pApp->getWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(this->m_pApp->getWindow(), GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS;
}

//--------------------------------------------------------------------------------
//
// PRIVATE METHODS
//
//--------------------------------------------------------------------------------

IOManager::IOManager(wolf::App *p_pApp)
{
    this->m_pApp = p_pApp;
    memset(m_bKeysDown, 0, sizeof(bool) * 256);
    memset(m_bKeysDownLast, 0, sizeof(bool) * 256);
}

IOManager::~IOManager()
{
    this->m_pApp = nullptr;
}

bool IOManager::isKeyDown(int key)
{
    return glfwGetKey(this->m_pApp->getWindow(), key) == GLFW_PRESS;
}