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

void EffectManager::removeEmittor(Emittor *p_pEmittor)
{
    if (p_pEmittor->areParticlesTransparent())
    {
        this->m_vpTransparentEmittors.erase(
            std::remove(this->m_vpTransparentEmittors.begin(), this->m_vpTransparentEmittors.end(), p_pEmittor),
            this->m_vpTransparentEmittors.end());
    }

    else
    {
        this->m_vpOpaqueEmittors.erase(
            std::remove(this->m_vpOpaqueEmittors.begin(), this->m_vpOpaqueEmittors.end(), p_pEmittor),
            this->m_vpOpaqueEmittors.end());
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

// void EffectManager::renderEmittors(const glm::mat4 &p_mProj, const glm::mat4 &p_mView)
// {
//     this->renderOpaqueEmittors(p_mProj, p_mView);
//
//     this->renderTransparentEmittors(p_mProj, p_mView);
// }

void EffectManager::renderOpaqueEmittors(const glm::mat4 &p_mProj, const glm::mat4 &p_mView)
{
    glEnable(GL_BLEND);
    for (auto emittor : this->m_vpOpaqueEmittors)
    {

        std::string blendMode = emittor->getEmittorBlendMode();

        if (blendMode.compare("additive") == 0)
        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_ONE, GL_ONE);
        }

        else if (blendMode.compare("interpolative") == 0)
        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }

        else if (blendMode.compare("disabled") == 0)
        {
            glDisable(GL_BLEND);
        }

        else
        {
            glDisable(GL_BLEND);
        }

        emittor->render(p_mProj, p_mView);
    }
    glDisable(GL_BLEND);
}

void EffectManager::renderTransparentEmittors(const glm::mat4 &p_mProj, const glm::mat4 &p_mView)
{
    glDepthMask(GL_FALSE);
    glEnable(GL_BLEND);
    for (auto emittor : this->m_vpTransparentEmittors)
    {
        std::string blendMode = emittor->getEmittorBlendMode();

        if (blendMode.compare("additive") == 0)
        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_ONE, GL_ONE);
        }

        else if (blendMode.compare("interpolative") == 0)
        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }

        else if (blendMode.compare("disabled") == 0)
        {
            glDisable(GL_BLEND);
        }

        else
        {
            glDisable(GL_BLEND);
        }

        emittor->render(p_mProj, p_mView);
    }
    glDisable(GL_BLEND);

    glDepthMask(GL_TRUE);
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