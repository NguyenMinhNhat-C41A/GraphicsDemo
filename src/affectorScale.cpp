#include "affectorScale.h"

//--------------------------------------------------------------------------------
//
// PUBLIC METHODS
//
//--------------------------------------------------------------------------------

Affector *AffectorScale::Factory(Emittor *p_pEmittor, tinyxml2::XMLNode *p_pXMLNode)
{
    AffectorScale *pAffScale = new AffectorScale(p_pEmittor);

    return pAffScale;
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

AffectorScale::AffectorScale(Emittor *p_pEmittor) : Affector(p_pEmittor)
{
}

void AffectorScale::affect(float p_dt)
{

    for (auto activeParticle = this->m_pEmittor->getActiveParticles()->getFirstParticle(); activeParticle != nullptr; activeParticle = activeParticle->getNextParticle())
    {
        activeParticle->scaleLinear(this->m_pEmittor->getDeltaScale() * (p_dt / activeParticle->getLifespan()));
    }
}
