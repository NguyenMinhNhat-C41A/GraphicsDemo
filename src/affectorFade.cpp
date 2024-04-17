#include "affectorFade.h"

//--------------------------------------------------------------------------------
//
// PUBLIC METHODS
//
//--------------------------------------------------------------------------------

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

Affector *AffectorFade::Factory(Emittor *p_pEmittor, tinyxml2::XMLNode *p_pXMLNode)
{
    AffectorFade *pAffFade = new AffectorFade(p_pEmittor);

    return pAffFade;
}

void AffectorFade::affect(float p_dt)
{

    for (auto activeParticle = this->m_pEmittor->getActiveParticles()->getFirstParticle(); activeParticle != nullptr; activeParticle = activeParticle->getNextParticle())
    {
        glm::vec4 colour = activeParticle->getColour();

        colour.a = 256.0f * (1.0f - static_cast<float>(activeParticle->getAge() / activeParticle->getLifespan()));

        activeParticle->setColour(colour);
    }
}

//--------------------------------------------------------------------------------
//
// PRIVATE METHODS
//
//--------------------------------------------------------------------------------

AffectorFade::AffectorFade(Emittor *p_pEmittor) : Affector(p_pEmittor)
{
}