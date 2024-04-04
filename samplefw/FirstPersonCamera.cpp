#include "FirstPersonCamera.h"

FirstPersonCamera::FirstPersonCamera(wolf::App *pApp) : m_pApp(pApp)
{
    this->lastMousePos = this->m_pApp->getMousePos();
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

    glm::vec2 mousePos = m_pApp->getMousePos();

    if (m_pApp->isKeyDown('w'))
    {
        this->camPosition += this->camSpeed * dt * glm::vec3(this->camMoveFront.x, 0.0f, this->camMoveFront.z);
    }
    if (m_pApp->isKeyDown('s'))
    {
        this->camPosition -= this->camSpeed * dt * glm::vec3(this->camMoveFront.x, 0.0f, this->camMoveFront.z);
    }

    if (m_pApp->isKeyDown('a'))
    {
        this->camPosition -= glm::normalize(glm::cross(this->camMoveFront, this->camUp)) * this->camSpeed * dt;
    }
    if (m_pApp->isKeyDown('d'))
    {
        this->camPosition += glm::normalize(glm::cross(this->camMoveFront, this->camUp)) * this->camSpeed * dt;
    }

    if (m_pApp->isKeyDown('f'))
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

    if (m_pApp->isKeyDown('r'))
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

    if (m_pApp->isKeyDown(GLFW_KEY_SPACE))
    {
        this->camPosition = glm::vec3(this->camPosition.x, this->camPosition.y + this->camFlySpeed * dt, this->camPosition.z);
    }

    if (m_pApp->isKeyDown(GLFW_KEY_LEFT_SHIFT))
    {
        this->camPosition = glm::vec3(this->camPosition.x, this->camPosition.y - this->camFlySpeed * dt, this->camPosition.z);
    }

    if (m_pApp->isKeyDown(GLFW_KEY_UP))
    {
        this->pitch += this->camTankRotSpeed * dt;
    }

    if (m_pApp->isKeyDown(GLFW_KEY_DOWN))
    {
        this->pitch -= this->camTankRotSpeed * dt;
    }

    if (m_pApp->isKeyDown(GLFW_KEY_LEFT))
    {
        this->yaw -= this->camTankRotSpeed * dt;
    }

    if (m_pApp->isKeyDown(GLFW_KEY_RIGHT))
    {
        this->yaw += this->camTankRotSpeed * dt;
    }

    float xOffset = mousePos.x - this->lastMousePos.x;
    float yOffset = mousePos.y - this->lastMousePos.y;
    this->lastMousePos.x = mousePos.x;
    this->lastMousePos.y = mousePos.y;

    this->yaw += xOffset * this->mouseSensitivity;

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
        this->pitch -= yOffset * this->mouseSensitivity;

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
    //     FirstPersonCamera::Frustum frustum;
    //
    //     glm::mat4 combinedMatrix = this->getProjMatrix() * this->getViewMatrix();
    //
    //     // Near plane
    //     frustum.nearPlane.normal = glm::vec3(combinedMatrix[3][0], combinedMatrix[3][1], combinedMatrix[3][2]) + glm::vec3(combinedMatrix[2][0], combinedMatrix[2][1], combinedMatrix[2][2]);
    //     frustum.nearPlane.distance = combinedMatrix[3][3] + combinedMatrix[2][3];
    //     frustum.nearPlane.tag = 1;
    //
    //     // Far plane
    //     frustum.farPlane.normal = glm::vec3(combinedMatrix[3][0], combinedMatrix[3][1], combinedMatrix[3][2]) - glm::vec3(combinedMatrix[2][0], combinedMatrix[2][1], combinedMatrix[2][2]);
    //     frustum.farPlane.distance = combinedMatrix[3][3] - combinedMatrix[2][3];
    //     frustum.farPlane.tag = 2;
    //
    //     // Right plane
    //     frustum.rightPlane.normal = glm::vec3(combinedMatrix[3][0], combinedMatrix[3][1], combinedMatrix[3][2]) - glm::vec3(combinedMatrix[0][0], combinedMatrix[0][1], combinedMatrix[0][2]);
    //     frustum.rightPlane.distance = combinedMatrix[3][3] - combinedMatrix[0][3];
    //     frustum.rightPlane.tag = 3;
    //
    //     // Left plane
    //     frustum.leftPlane.normal = glm::vec3(combinedMatrix[3][0], combinedMatrix[3][1], combinedMatrix[3][2]) + glm::vec3(combinedMatrix[0][0], combinedMatrix[0][1], combinedMatrix[0][2]);
    //     frustum.leftPlane.distance = combinedMatrix[3][3] + combinedMatrix[0][3];
    //     frustum.leftPlane.tag = 4;
    //
    //     // Top plane
    //     frustum.topPlane.normal = glm::vec3(combinedMatrix[3][0], combinedMatrix[3][1], combinedMatrix[3][2]) - glm::vec3(combinedMatrix[1][0], combinedMatrix[1][1], combinedMatrix[1][2]);
    //     frustum.topPlane.distance = combinedMatrix[3][3] - combinedMatrix[1][3];
    //     frustum.topPlane.tag = 5;
    //
    //     // Bottom plane
    //     frustum.bottomPlane.normal = glm::vec3(combinedMatrix[3][0], combinedMatrix[3][1], combinedMatrix[3][2]) + glm::vec3(combinedMatrix[1][0], combinedMatrix[1][1], combinedMatrix[1][2]);
    //     frustum.bottomPlane.distance = combinedMatrix[3][3] + combinedMatrix[1][3];
    //     frustum.bottomPlane.tag = 6;
    //
    //     float normalLength = 0.0f;
    //
    //     normalLength = glm::length(frustum.leftPlane.normal);
    //     frustum.leftPlane.normal = glm::normalize(frustum.leftPlane.normal);
    //     // frustum.leftPlane.distance /= normalLength;
    //
    //     normalLength = glm::length(frustum.rightPlane.normal);
    //     frustum.rightPlane.normal = glm::normalize(frustum.rightPlane.normal);
    //     // frustum.rightPlane.distance /= normalLength;
    //
    //     normalLength = glm::length(frustum.topPlane.normal);
    //     frustum.topPlane.normal = glm::normalize(frustum.topPlane.normal);
    //     // frustum.topPlane.distance /= normalLength;
    //
    //     normalLength = glm::length(frustum.bottomPlane.normal);
    //     frustum.bottomPlane.normal = glm::normalize(frustum.bottomPlane.normal);
    //     // frustum.bottomPlane.distance /= normalLength;
    //
    //     normalLength = glm::length(frustum.nearPlane.normal);
    //     frustum.nearPlane.normal = glm::normalize(frustum.nearPlane.normal);
    //     // frustum.nearPlane.distance /= normalLength;
    //
    //     normalLength = glm::length(frustum.farPlane.normal);
    //     frustum.farPlane.normal = glm::normalize(frustum.farPlane.normal);
    //     // frustum.farPlane.distance /= normalLength;
    //
    //     //     return frustum;
    //
    glm::vec2 screenSize = this->m_pApp->getScreenSize();
    const float aspectRatio = screenSize.x / screenSize.y;

    const float halfV = this->m_far * glm::tan(this->m_fov * 0.5f);
    const float halfH = halfV * aspectRatio;

    //     std::cout << "halfV: " << halfV << std::endl;
    //
    //     std::cout << "halfH: " << halfH << std::endl;
    //
    //     std::cout << "FPS - CAMPOS: " << this->camPosition.x << ", " << this->camPosition.y << ", " << this->camPosition.z << std::endl;

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

    // std::cout << "FPS - NEARPLANE_NORMAL: " << frustum.nearPlane.normal.x << ", " << frustum.nearPlane.normal.y << ", " << frustum.nearPlane.normal.z << std::endl;
    // std::cout << "FPS - FARPLANE_NORMAL: " << frustum.farPlane.normal.x << ", " << frustum.farPlane.normal.y << ", " << frustum.farPlane.normal.z << std::endl;
    // std::cout << "FPS - RIGHTPLANE_NORMAL: " << frustum.rightPlane.normal.x << ", " << frustum.rightPlane.normal.y << ", " << frustum.rightPlane.normal.z << std::endl;
    // std::cout << "FPS - LEFTPLANE_NORMAL: " << frustum.leftPlane.normal.x << ", " << frustum.leftPlane.normal.y << ", " << frustum.leftPlane.normal.z << std::endl;
    // std::cout << "FPS - TOPPLANE_NORMAL: " << frustum.topPlane.normal.x << ", " << frustum.topPlane.normal.y << ", " << frustum.topPlane.normal.z << std::endl;
    // std::cout << "FPS - BOTTOMPLANE_NORMAL: " << frustum.bottomPlane.normal.x << ", " << frustum.bottomPlane.normal.y << ", " << frustum.bottomPlane.normal.z << std::endl;

    return frustum;
}