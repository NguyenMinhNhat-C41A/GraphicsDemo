#include "affectorScale.h"

//--------------------------------------------------------------------------------
//
// PUBLIC METHODS
//
//--------------------------------------------------------------------------------

AffectorScale::AffectorScale(Emittor *p_pEmittor) : Affector(p_pEmittor)
{
}

AffectorScale::~AffectorScale()
{
}

void AffectorScale::update(float p_dt)
{
    this->m_pTimer += p_dt;
    this->affect(p_dt);
}

//--------------------------------------------------------------------------------
//
// PRIVATE METHODS
//
//--------------------------------------------------------------------------------

void AffectorScale::affect(float p_dt)
{
    for (auto particle = this->m_pEmittor->getActiveParticles()->getFirstParticle(); particle != nullptr; particle = particle->getNextParticle())
    {
        particle->scaleLinear((this->m_pEmittor->getDeltaScale() / this->m_pEmittor->getParticleLifespan()) * p_dt);
    }

    glm::vec3 firstParticleScale = this->m_pEmittor->getActiveParticles()->getFirstParticle()->getTransform()->getScale();
}
