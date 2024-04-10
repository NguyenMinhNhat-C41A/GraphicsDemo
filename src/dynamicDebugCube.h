#pragma once
#include "../thirdparty/tinyxml2/tinyxml2.h"
#include "rng.h"
#include "factoryMethodsManager.h"
#include "debugCube.h"

class DynamicDebugCube : public DebugCube
{
public:
    static Node *Factory(tinyxml2::XMLNode *p_xmlNode);

    DynamicDebugCube();
    // DynamicDebugCube(std::string p_newName, const glm::vec3 &p_vNewSc, const glm::vec3 &p_vNewRo, const glm::vec3 &p_vNewTr);

    ~DynamicDebugCube();
    virtual void update(float p_dt) override;

private:
    float m_fOrbitRadius = 0.0f;
    float m_fCounter = 0.0f;
    float yPos = 0.0f;
    float m_fOrbitDir = 0.0f;
    glm::vec3 m_vRotDir = glm::vec3(1.0f);
    glm::vec3 m_vTrlOffset = glm::vec3(0.0f);
    glm::vec3 m_vRotOffset = glm::vec3(0.0f);

    float m_fOrbitSpeed = 0.25f;
    float m_fRotateSpeed = 128.0f;
};