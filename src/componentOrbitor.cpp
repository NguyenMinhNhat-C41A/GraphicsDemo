#include "componentOrbitor.h"

//--------------------------------------------------------------------------------
//
// PUBLIC METHODS
//
//--------------------------------------------------------------------------------

ComponentBase *ComponentOrbitor::Factory(Node *p_pCompNode, tinyxml2::XMLNode *p_pXMLNode)
{
    ComponentOrbitor *pOrbitorComp = new ComponentOrbitor(p_pCompNode);

    return pOrbitorComp;
}

ComponentOrbitor::~ComponentOrbitor()
{
}

void ComponentOrbitor::init()
{
}

void ComponentOrbitor::update(float dt)
{
    this->m_fCounter += dt;

    this->m_pCompNode->setTranslate(this->m_vTrlOffset +
                                    glm::vec3(
                                        this->m_fOrbitRadius * glm::sin(this->m_fCounter * this->m_fOrbitSpeed),
                                        this->yPos,
                                        this->m_fOrbitRadius * glm::cos(this->m_fCounter * this->m_fOrbitSpeed)));

    this->m_pCompNode->setRotate(this->m_pCompNode->getRotate() + this->m_vRotDir * dt * this->m_fRotateSpeed);
}

//--------------------------------------------------------------------------------
//
// PRIVATE METHODS
//
//--------------------------------------------------------------------------------

ComponentOrbitor::ComponentOrbitor(Node *p_pCompNode) : ComponentBase(p_pCompNode)
{
    this->m_fOrbitRadius = glm::length(p_pCompNode->getGlobalTranslate());
    this->yPos = p_pCompNode->getGlobalTranslate().y;
    this->m_vRotOffset = p_pCompNode->getRotate();
    this->m_vRotDir = glm::vec3(1.0f);
    this->m_fOrbitDir = (RandomNumberGenerator::getRandomNumber(0, 1) - 0.5f) * 2.0f;
    this->m_vTrlOffset = p_pCompNode->getGlobalTranslate();
}
