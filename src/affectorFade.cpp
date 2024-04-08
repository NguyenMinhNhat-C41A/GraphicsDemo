#include "affectorFade.h"

//--------------------------------------------------------------------------------
//
// PUBLIC METHODS
//
//--------------------------------------------------------------------------------

AffectorFade::AffectorFade(Emittor *p_pEmittor) : Affector(p_pEmittor)
{
}

AffectorFade::~AffectorFade()
{
}

void AffectorFade::update(float p_dt)
{
    this->m_pTimer += p_dt;
    this->affect(p_dt);
}

//--------------------------------------------------------------------------------
//
// PRIVATE METHODS
//
//--------------------------------------------------------------------------------

void AffectorFade::affect(float p_dt)
{

    for (auto activeParticle = this->m_pEmittor->getActiveParticles()->getFirstParticle(); activeParticle != nullptr; activeParticle = activeParticle->getNextParticle())
    {
        glm::vec4 colour = activeParticle->getColour();

        colour.a = colour.a * (activeParticle->getAge() / activeParticle->getLifespan());

        activeParticle->setColour(colour);
    }
}
