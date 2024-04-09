#include "EffectManager.h"

EffectManager *EffectManager::s_pEffectManager = nullptr;
void EffectManager::createInstance(wolf::App *p_pApp)
{
    assert(EffectManager::s_pEffectManager == nullptr);
    EffectManager::s_pEffectManager = new EffectManager(p_pApp);
}
void EffectManager::destroyInstance()
{
    assert(EffectManager::s_pEffectManager != nullptr);
    delete EffectManager::s_pEffectManager;
    EffectManager::s_pEffectManager = nullptr;
}
EffectManager *EffectManager::Instance()
{
    return EffectManager::s_pEffectManager;
}

void EffectManager::addEffect(ComponentEffect *compEffect)
{
    this->m_vpEffects.push_back(compEffect);
    // printf("FXMNGR - EFFECT_ADDED: %d\n", this->m_vpEffects.size());
}

void EffectManager::removeEffect(ComponentEffect *compEffect)
{
    for (int i = 0; i < this->m_vpEffects.size(); i++)
    {
        ComponentEffect *comp = this->m_vpEffects.at(i);
        if (comp == compEffect)
        {
            this->m_vpEffects.erase(this->m_vpEffects.begin() + i);
            break;
        }
    }
}

void EffectManager::updateEffectsEmittors(float p_dt)
{

    for (auto effect : this->m_vpEffects)
    {
        effect->updateEmittors(p_dt);
    }
}

void EffectManager::renderEffectsEmittors(const glm::mat4 &p_mProj, const glm::mat4 &p_mView)
{
    for (auto effect : this->m_vpEffects)
    {
        glDepthMask(GL_TRUE);
        effect->renderEmittors(p_mProj, p_mView);
        glDepthMask(GL_TRUE);
    }
}

//--------------------------------------------------------------------------------
//
// PRIVATE METHODS
//
//--------------------------------------------------------------------------------

EffectManager::EffectManager(wolf::App *p_pApp)
{
}
EffectManager::~EffectManager()
{
}