#pragma once

#include "../thirdparty/tinyxml2/tinyxml2.h"
#include "componentBase.h"

class ComponentOrbitor : public ComponentBase
{
public:
    //--------------------------------------------------------------------------------
    //
    // PUBLIC METHODS
    //
    //--------------------------------------------------------------------------------

    static ComponentBase *Factory(Node *p_pCompNode, tinyxml2::XMLNode *p_pXMLNode);
    ~ComponentOrbitor();

    virtual std::string ComponentID() override { return "GOC_Orbitor"; };

    virtual void init() override;
    virtual void update(float dt) override;

private:
    //--------------------------------------------------------------------------------
    //
    // PRIVATE METHODS
    //
    //--------------------------------------------------------------------------------

    ComponentOrbitor(Node *p_pCompNode);

    //--------------------------------------------------------------------------------
    //
    // PRIVATE VARIABLES
    //
    //--------------------------------------------------------------------------------

    float m_fOrbitSpeed = 0.25f;
    float m_fRotateSpeed = 128.0f;

    float m_fOrbitRadius = 0.0f;
    float m_fOrbitDir = 1.0f;
    float yPos = 0.0f;

    float m_fCounter = 0.0f;

    glm::vec3 m_vRotOffset = glm::vec3(0.0f);
    glm::vec3 m_vRotDir = glm::vec3(1.0f);

    glm::vec3 m_vTrlOffset = glm::vec3(0.0f);
};