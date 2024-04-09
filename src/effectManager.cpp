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

void EffectManager::addEmittor(Emittor *p_pEmittor)
{
    if (p_pEmittor->areParticlesTransparent())
    {
        this->m_vpTransparentEmittors.push_back(p_pEmittor);
    }
    else
    {
        this->m_vpOpaqueEmittors.push_back(p_pEmittor);
    }
}

void EffectManager::updateEmittors(float p_dt)
{
    for (auto emittor : this->m_vpOpaqueEmittors)
    {
        emittor->update(p_dt);
    }

    for (auto emittor : this->m_vpTransparentEmittors)
    {
        emittor->update(p_dt);
    }
}

void EffectManager::renderOpaqueEmittors(const glm::mat4 &p_mProj, const glm::mat4 &p_mView)
{
    for (auto emittor : this->m_vpOpaqueEmittors)
    {
        emittor->render(p_mProj, p_mView);
    }
}

void EffectManager::renderTransparentEmittors(const glm::mat4 &p_mProj, const glm::mat4 &p_mView)
{
    for (auto emittor : this->m_vpTransparentEmittors)
    {
        emittor->render(p_mProj, p_mView);
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