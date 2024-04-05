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

    for (auto particle = this->m_pEmittor->getActiveParticles()->getFirstParticle(); particle != nullptr; particle = particle->getNextParticle())
    {
    }
}
