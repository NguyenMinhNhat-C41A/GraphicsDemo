#include "FirstPersonCamera.h"

FirstPersonCamera::FirstPersonCamera(wolf::App *pApp) : m_pApp(pApp)
{
    this->camSpeed = this->camSpeeds.at(this->camSpeedIndex);
    this->camFlySpeed = this->camSpeeds.at(this->camSpeedIndex);
}

FirstPersonCamera::~FirstPersonCamera()
{
}

glm::mat4 FirstPersonCamera::getViewMatrix()
{
    return glm::lookAt(this->camPosition, this->camPosition + this->camViewFront, this->camUp);
}

glm::mat4 FirstPersonCamera::getProjMatrix()
{
    return glm::perspective(this->m_fov, this->m_pApp->getScreenSize().x / this->m_pApp->getScreenSize().y, this->m_near, this->m_far);
}

void FirstPersonCamera::update(const float dt)
{

    if (IOManager::Instance()->isButtonPressed('W'))
    {
        this->camPosition += this->camSpeed * dt * glm::vec3(this->camMoveFront.x, 0.0f, this->camMoveFront.z);
    }
    if (IOManager::Instance()->isButtonPressed('S'))
    {
        this->camPosition -= this->camSpeed * dt * glm::vec3(this->camMoveFront.x, 0.0f, this->camMoveFront.z);
    }

    if (IOManager::Instance()->isButtonPressed('A'))
    {
        this->camPosition -= glm::normalize(glm::cross(this->camMoveFront, this->camUp)) * this->camSpeed * dt;
    }
    if (IOManager::Instance()->isButtonPressed('D'))
    {
        this->camPosition += glm::normalize(glm::cross(this->camMoveFront, this->camUp)) * this->camSpeed * dt;
    }

    if (IOManager::Instance()->isButtonPressed('F'))
    {
        if (!this->m_bIsFDown)
        {
            this->m_bIsFDown = true;
        }
    }
    else
    {
        if (this->m_bIsFDown)
        {
            this->m_bIsFDown = false;
            this->m_bIsWheelchairMode = !this->m_bIsWheelchairMode;
        }
    }

    if (IOManager::Instance()->isButtonPressed('R'))
    {
        if (!this->m_bIsRDown)
        {
            this->m_bIsRDown = true;
        }
    }
    else
    {
        if (this->m_bIsRDown)
        {
            this->m_bIsRDown = false;

            this->camSpeedIndex = (this->camSpeedIndex + 1) % this->camSpeeds.size();
            this->camSpeed = this->camSpeeds.at(this->camSpeedIndex);
            this->camFlySpeed = this->camSpeeds.at(this->camSpeedIndex);
        }
    }

    if (IOManager::Instance()->isButtonPressed(GLFW_KEY_SPACE))
    {
        this->camPosition = glm::vec3(this->camPosition.x, this->camPosition.y + this->camFlySpeed * dt, this->camPosition.z);
    }

    if (IOManager::Instance()->isButtonPressed(GLFW_KEY_LEFT_SHIFT))
    {
        this->camPosition = glm::vec3(this->camPosition.x, this->camPosition.y - this->camFlySpeed * dt, this->camPosition.z);
    }

    if (IOManager::Instance()->isButtonPressed(GLFW_KEY_UP))
    {
        this->pitch += this->camTankRotSpeed * dt;
    }

    if (IOManager::Instance()->isButtonPressed(GLFW_KEY_DOWN))
    {
        this->pitch -= this->camTankRotSpeed * dt;
    }

    if (IOManager::Instance()->isButtonPressed(GLFW_KEY_LEFT))
    {
        this->yaw -= this->camTankRotSpeed * dt;
    }

    if (IOManager::Instance()->isButtonPressed(GLFW_KEY_RIGHT))
    {
        this->yaw += this->camTankRotSpeed * dt;
    }

    this->yaw += IOManager::Instance()->getMouseOffset().first * IOManager::Instance()->getMouseSensitivity();

    if (this->yaw < -180.0f)
    {
        this->yaw = 180.0f;
    }

    if (this->yaw > 180.0f)
    {
        this->yaw = -180.0f;
    }

    if (this->m_bIsWheelchairMode)
    {
        this->pitch = 0.0f;
    }
    else
    {
        this->pitch -= IOManager::Instance()->getMouseOffset().second * IOManager::Instance()->getMouseSensitivity();

        if (this->pitch > MAX_PITCH)
        {
            this->pitch = MAX_PITCH;
        }

        if (this->pitch < -MAX_PITCH)
        {
            this->pitch = -MAX_PITCH;
        }
    }
    glm::vec3 moveDirection = glm::vec3(
        cos(glm::radians(this->yaw)),
        0.0f,
        sin(glm::radians(this->yaw)));
    this->camMoveFront = glm::normalize(moveDirection);

    glm::vec3 lookDirection = glm::vec3(
        moveDirection.x * cos(glm::radians(this->pitch)),
        sin(glm::radians(this->pitch)),
        moveDirection.z * cos(glm::radians(this->pitch)));
    this->camViewFront = glm::normalize(lookDirection);
}
//-------------------------------------
// TODO: Add dirty bit to calculate frustum
//-------------------------------------
FirstPersonCamera::Frustum FirstPersonCamera::getFrustum()
{

    glm::vec2 screenSize = this->m_pApp->getScreenSize();
    const float aspectRatio = screenSize.x / screenSize.y;

    const float halfV = this->m_far * glm::tan(this->m_fov * 0.5f);
    const float halfH = halfV * aspectRatio;

    FirstPersonCamera::Frustum frustum;

    glm::vec3 camRight = glm::normalize(glm::cross(this->camViewFront, this->camUp));
    glm::vec3 camDynamicUp = glm::normalize(glm::cross(camRight, this->camViewFront));
    glm::vec3 farFront = this->m_far * glm::normalize(this->camViewFront);

    glm::vec3 point = glm::vec3(0.0f);
    glm::vec3 normal = glm::vec3(0.0f);

    point = this->camPosition + this->m_near * this->camViewFront;
    normal = glm::normalize(this->camViewFront);

    frustum.nearPlane = {normal, -glm::dot(normal, point), 1};

    point = this->camPosition + this->m_far * this->camViewFront;
    normal = glm::normalize(-this->camViewFront);
    frustum.farPlane = {normal, -glm::dot(normal, point), 2};

    point = this->camPosition;
    normal = glm::normalize(glm::cross(camDynamicUp, farFront + camRight * halfH));
    frustum.rightPlane = {normal, -glm::dot(normal, point), 3};

    point = this->camPosition;
    normal = glm::normalize(glm::cross(farFront - camRight * halfH, camDynamicUp));
    frustum.leftPlane = {normal, -glm::dot(normal, point), 4};

    point = this->camPosition;
    normal = glm::normalize(glm::cross(farFront + camDynamicUp * halfV, camRight));
    frustum.topPlane = {normal, -glm::dot(normal, point), 5};

    point = this->camPosition;
    normal = glm::normalize(glm::cross(camRight, farFront - camDynamicUp * halfV));
    frustum.bottomPlane = {normal, -glm::dot(normal, point), 6};

    return frustum;
}