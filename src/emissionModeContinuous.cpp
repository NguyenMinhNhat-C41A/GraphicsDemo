#include "emissionModeContinuous.h"

//--------------------------------------------------------------------------------
//
// PUBLIC METHODS
//
//--------------------------------------------------------------------------------

EmissionMode *EmissionModeContinuous::Factory(Emittor *p_pEmittor, tinyxml2::XMLNode *p_pXMLNode)
{
    EmissionModeContinuous *emmoCont = new EmissionModeContinuous(p_pEmittor);

    tinyxml2::XMLNode *pXMLPropertiesNode = p_pXMLNode->FirstChild();

    while (pXMLPropertiesNode != nullptr)
    {
        std::string propTag = pXMLPropertiesNode->Value();

        if (propTag.compare("EmissionDelay") == 0)
        {
            float delay = 2.0f;

            if (pXMLPropertiesNode->ToElement()->QueryFloatAttribute("time", &delay) != tinyxml2::XML_SUCCESS)
            {
                printf("EMMOCONT - DEFAULT_EMISSION_DELAY\n");
            }

            emmoCont->m_fEmissionDelay = delay;
        }

        pXMLPropertiesNode = pXMLPropertiesNode->NextSibling();
    }

    return emmoCont;
}

EmissionModeContinuous::EmissionModeContinuous(Emittor *p_pEmittor) : EmissionMode(p_pEmittor)
{
}

EmissionModeContinuous::~EmissionModeContinuous()
{
}

void EmissionModeContinuous::update(float p_dt)
{
    this->m_pTimer += p_dt;
    this->m_fDurationTimer += p_dt;

    if ((this->m_pEmittor->getEmittorDuration() < 0) ||
        (this->m_pEmittor->getEmittorDuration() >= 0) && (this->m_fDurationTimer < this->m_pEmittor->getEmittorDuration()))
    {
        if (this->m_pTimer >= this->m_fEmissionDelay)
        {
            this->emit();
            this->m_pTimer = 0.0f;
        }
    }
}
//--------------------------------------------------------------------------------
//
// PRIVATE METHODS
//
//--------------------------------------------------------------------------------

void EmissionModeContinuous::emit()
{
    Shape *emittorShape = this->m_pEmittor->getEmittorShape();

    glm::vec2 shapeMinMaxX = emittorShape->getMinMaxX();
    glm::vec2 shapeMinMaxY = emittorShape->getMinMaxY();
    glm::vec2 shapeMinMaxZ = emittorShape->getMinMaxZ();

    glm::vec3 newParticlePos = glm::vec3(
                                   RandomNumberGenerator::getRandomDecimal(shapeMinMaxX.x, shapeMinMaxX.y),
                                   RandomNumberGenerator::getRandomDecimal(shapeMinMaxY.x, shapeMinMaxY.y),
                                   RandomNumberGenerator::getRandomDecimal(shapeMinMaxZ.x, shapeMinMaxZ.y)) +
                               this->m_pEmittor->getOffset();

    glm::vec3 newDirection = glm::normalize(glm::vec3(
        RandomNumberGenerator::getRandomNumber(1, 64) * (RandomNumberGenerator::getRandomNumber(0, 1) - 0.5f) * 2.0f,
        RandomNumberGenerator::getRandomNumber(1, 64) * (RandomNumberGenerator::getRandomNumber(0, 1) - 0.5f) * 2.0f,
        RandomNumberGenerator::getRandomNumber(1, 64) * (RandomNumberGenerator::getRandomNumber(0, 1) - 0.5f) * 2.0f));

    float newLifespan = this->m_pEmittor->getParticleBaseLifespan() + static_cast<float>(RandomNumberGenerator::getRandomNumber(0, 128) / 64.0f);

    this->m_pEmittor->activateParticle(
        newParticlePos,
        this->m_pEmittor->getStartScale(),
        newDirection,
        this->m_pEmittor->getDefaultColour(),
        newLifespan);
}
