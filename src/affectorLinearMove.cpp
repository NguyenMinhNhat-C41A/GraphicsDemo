#include "affectorLinearMove.h"

//--------------------------------------------------------------------------------
//
// PUBLIC METHODS
//
//--------------------------------------------------------------------------------

Affector *AffectorLinearMove::Factory(Emittor *p_pEmittor, tinyxml2::XMLNode *p_pXMLNode)
{
    AffectorLinearMove *pAffLiMo = new AffectorLinearMove(p_pEmittor);

    tinyxml2::XMLNode *pXMLPropertiesNode = p_pXMLNode->FirstChild();

    while (pXMLPropertiesNode != nullptr)
    {
        std::string propTag = pXMLPropertiesNode->Value();

        if (propTag.compare("Velocity") == 0)
        {
            glm::vec3 velocity = glm::vec3(1.0f);

            if (pXMLPropertiesNode->ToElement()->QueryFloatAttribute("x", &velocity.x))
            {
                printf("AFFLIMO - DEFAULT_DIRECTION_X\n");
            }

            if (pXMLPropertiesNode->ToElement()->QueryFloatAttribute("y", &velocity.y))
            {
                printf("AFFLIMO - DEFAULT_DIRECTION_Y\n");
            }

            if (pXMLPropertiesNode->ToElement()->QueryFloatAttribute("z", &velocity.z))
            {
                printf("AFFLIMO - DEFAULT_DIRECTION_Z\n");
            }

            pAffLiMo->m_vVelocity = velocity;
        }

        else if (propTag.compare("IsMoveOnParticleDirection") == 0)
        {
            bool isMOPD = false;
            if (pXMLPropertiesNode->ToElement()->QueryBoolAttribute("isMOPD", &isMOPD))
            {
                printf("AFFLIMO - DEFAULT_IS_MOPD\n");
            }
            pAffLiMo->m_bIsMoveOnParticleDirection = isMOPD;
        }

        pXMLPropertiesNode = pXMLPropertiesNode->NextSibling();
    }

    return pAffLiMo;
}

AffectorLinearMove::AffectorLinearMove(Emittor *p_pEmittor) : Affector(p_pEmittor)
{
    this->m_vVelocity = glm::vec3(1.0f);
    this->m_bIsMoveOnParticleDirection = false;
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

void AffectorLinearMove::affect(float p_dt)
{
    Emittor::ParticlesList *activeParticles = this->m_pEmittor->getActiveParticles();

    if (this->m_bIsMoveOnParticleDirection)
    {
        float speed = glm::length(this->m_vVelocity);
        for (auto particle = this->m_pEmittor->getActiveParticles()->getFirstParticle(); particle != nullptr; particle = particle->getNextParticle())
        {
            particle->translateOnDirection(p_dt * speed);
        }
    }
    else
    {
        for (auto particle = this->m_pEmittor->getActiveParticles()->getFirstParticle(); particle != nullptr; particle = particle->getNextParticle())
        {
            particle->translate(this->m_vVelocity * p_dt);
        }
    }
}