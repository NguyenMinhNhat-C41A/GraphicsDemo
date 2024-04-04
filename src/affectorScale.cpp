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
    Emittor::ParticlesList *activeParticles = this->m_pEmittor->getActiveParticles();

    for (auto particle = this->m_pEmittor->getActiveParticles()->getFirstParticle(); particle != nullptr; particle = particle->getNextParticle())
    {
        particle->scaleLinear(glm::vec3(p_dt / 2.0f));
    }
}
