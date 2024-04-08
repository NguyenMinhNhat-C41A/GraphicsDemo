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

        if (propTag.compare("Direction") == 0)
        {
            glm::vec3 direction = glm::vec3(1.0f);

            if (pXMLPropertiesNode->ToElement()->QueryFloatAttribute("x", &direction.x))
            {
                printf("AFFLIMO - DEFAULT_DIRECTION_X\n");
            }

            if (pXMLPropertiesNode->ToElement()->QueryFloatAttribute("y", &direction.y))
            {
                printf("AFFLIMO - DEFAULT_DIRECTION_Y\n");
            }

            if (pXMLPropertiesNode->ToElement()->QueryFloatAttribute("z", &direction.z))
            {
                printf("AFFLIMO - DEFAULT_DIRECTION_Z\n");
            }

            pAffLiMo->m_vDirection = direction;
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
    this->m_vDirection = glm::vec3(1.0f);
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
        for (auto particle = this->m_pEmittor->getActiveParticles()->getFirstParticle(); particle != nullptr; particle = particle->getNextParticle())
        {
            particle->translateOnDirection(p_dt * 10.0f);
        }
    }
    else
    {
        for (auto particle = this->m_pEmittor->getActiveParticles()->getFirstParticle(); particle != nullptr; particle = particle->getNextParticle())
        {
            particle->translate(this->m_vDirection * p_dt);
        }
    }
}