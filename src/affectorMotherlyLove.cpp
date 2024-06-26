#include "affectorMotherlyLove.h"

//--------------------------------------------------------------------------------
//
// PUBLIC METHODS
//
//--------------------------------------------------------------------------------

AffectorMotherlyLove::~AffectorMotherlyLove()
{
}

void AffectorMotherlyLove::update(float p_dt)
{
    this->m_pTimer += p_dt;
    this->affect(p_dt);
}

//--------------------------------------------------------------------------------
//
// PRIVATE METHODS
//
//--------------------------------------------------------------------------------

Affector *AffectorMotherlyLove::Factory(Emittor *p_pEmittor, tinyxml2::XMLNode *p_pXMLNode)
{

    AffectorMotherlyLove *pAffMotherlyLove = new AffectorMotherlyLove(p_pEmittor);
    return pAffMotherlyLove;
}

void AffectorMotherlyLove::affect(float p_dt)
{

    std::vector<Node *> children = this->m_pMother->getImmediateChildren();
    if (this->m_bCount > 0)
    {
        if (children.size() > 0)
        {
            for (auto activeParticle = this->m_pEmittor->getActiveParticles()->getFirstParticle(); activeParticle != nullptr; activeParticle = activeParticle->getNextParticle())
            {
                glm::vec3 distance = this->m_pChildMostDear->getGlobalTranslate() - activeParticle->getTransform()->getTranslate();
                float remainingLife = activeParticle->getLifespan() - activeParticle->getAge();

                float updatesCount = remainingLife / p_dt;
                glm::vec3 stepSize = distance / updatesCount;

                activeParticle->translate(stepSize);
            }
        }
    }

    else
    {
        if (children.size() > 0)
        {
            this->m_pChildMostDear = children.at(0);
        }
    }

    this->m_bCount = children.size();
}

//--------------------------------------------------------------------------------
//
// PRIVATE METHODS
//
//--------------------------------------------------------------------------------

AffectorMotherlyLove::AffectorMotherlyLove(Emittor *p_pEmittor) : Affector(p_pEmittor)
{

    this->m_pMother = p_pEmittor->getHostComponent()->getComponentNode();

    std::vector<Node *> children = this->m_pMother->getImmediateChildren();
    this->m_bCount = children.size();
    if (this->m_bCount > 0)
    {
        this->m_pChildMostDear = children.at(0);
    }
}