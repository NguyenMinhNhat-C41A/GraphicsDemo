#include "affectorLinearMove.h"

//--------------------------------------------------------------------------------
//
// PUBLIC METHODS
//
//--------------------------------------------------------------------------------

AffectorLinearMove::AffectorLinearMove(Emittor *p_pEmittor) : Affector(p_pEmittor)
{
}

AffectorLinearMove::~AffectorLinearMove()
{
}
void AffectorLinearMove::update(float p_dt)
{
    this->m_pTimer += p_dt;
    this->affect(p_dt);
}

//--------------------------------------------------------------------------------
//
// PRIVATE METHODS
//
//--------------------------------------------------------------------------------

Affector *AffectorLinearMove::Factory(Emittor *p_pEmittor, tinyxml2::XMLNode *p_pXMLNode)
{
    AffectorLinearMove *pAffLiMo = new AffectorLinearMove(p_pEmittor);

    return pAffLiMo;
}

void AffectorLinearMove::affect(float p_dt)
{
    Emittor::ParticlesList *activeParticles = this->m_pEmittor->getActiveParticles();

    for (auto particle = this->m_pEmittor->getActiveParticles()->getFirstParticle(); particle != nullptr; particle = particle->getNextParticle())
    {
        particle->translateOnDirection(p_dt * 10.0f);
    }
}