#include "componentEffect.h"

//--------------------------------------------------------------------------------
//
// PUBLIC METHODS
//
//--------------------------------------------------------------------------------

ComponentEffect ::~ComponentEffect()
{
    for (auto emittor : this->m_vEmittors)
    {
        EffectManager::Instance()->removeEmittor(emittor);
        delete emittor;
        emittor = nullptr;
    }
    this->m_vEmittors.clear();
}

ComponentBase *ComponentEffect::Factory(Node *p_pCompNode, tinyxml2::XMLNode *p_pXMLNode)
{
    ComponentEffect *pEffectComp = new ComponentEffect(p_pCompNode);
    tinyxml2::XMLNode *pXMLPropertiesNode = p_pXMLNode->FirstChild();
    while (pXMLPropertiesNode != nullptr)
    {
        std::string propTag = pXMLPropertiesNode->Value();
        if (propTag.compare("Emittor") == 0)
        {
            Emittor *emittor = Emittor::Factory(pEffectComp, pXMLPropertiesNode);
            pEffectComp->addEmittor(emittor);
        }

        pXMLPropertiesNode = pXMLPropertiesNode->NextSibling();
    }

    return pEffectComp;
}

void ComponentEffect::init()
{
    tinyxml2::XMLDocument *doc = nullptr;
}

void ComponentEffect::update(float dt)
{
}

void ComponentEffect::addEmittor(Emittor *p_pEmittor)
{
    this->m_vEmittors.push_back(p_pEmittor);
    EffectManager::Instance()->addEmittor(p_pEmittor);
}

glm::vec3 ComponentEffect::getGlobalTranslate()
{
    return this->m_pCompNode->getGlobalTranslate();
}

//--------------------------------------------------------------------------------
//
// PRIVATE METHODS
//
//--------------------------------------------------------------------------------

ComponentEffect::ComponentEffect(Node *p_pCompNode) : ComponentBase(p_pCompNode)
{
}