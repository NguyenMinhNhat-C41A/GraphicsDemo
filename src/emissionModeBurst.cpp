#include "emissionModeBurst.h"

//--------------------------------------------------------------------------------
//
// PUBLIC METHODS
//
//--------------------------------------------------------------------------------

EmissionMode *EmissionModeBurst::Factory(Emittor *p_pEmittor, tinyxml2::XMLNode *p_pXMLNode)
{
    EmissionModeBurst *emmoBrst = new EmissionModeBurst(p_pEmittor);

    tinyxml2::XMLNode *pXMLPropertiesNode = p_pXMLNode->FirstChild();

    while (pXMLPropertiesNode != nullptr)
    {
        std::string propTag = pXMLPropertiesNode->Value();

        if (propTag.compare("EmissionDelay") == 0)
        {
            float delay = 2.0f;

            if (pXMLPropertiesNode->ToElement()->QueryFloatAttribute("time", &delay) != tinyxml2::XML_SUCCESS)
            {
                printf("EMMOBRST - DEFAULT_EMISSION_DELAY\n");
            }

            emmoBrst->m_fEmissionDelay = delay;
        }

        pXMLPropertiesNode = pXMLPropertiesNode->NextSibling();
    }

    return emmoBrst;
}

EmissionModeBurst::~EmissionModeBurst()
{
}

void EmissionModeBurst::update(float p_dt)
{
    this->m_pTimer += p_dt;
    if (this->m_pTimer >= this->m_fEmissionDelay)
    {
        this->m_pTimer = 0.0f;
        this->emit();
    }
}

//--------------------------------------------------------------------------------
//
// PRIVATE METHODS
//
//--------------------------------------------------------------------------------

EmissionModeBurst::EmissionModeBurst(Emittor *p_pEmittor) : EmissionMode(p_pEmittor)
{
}

void EmissionModeBurst::emit()
{
    Shape *emittorShape = this->m_pEmittor->getEmittorShape();
    std::string emittorShapeType = emittorShape->getShapeType();

    glm::vec2 shapeMinMaxX = emittorShape->getMinMaxX();
    glm::vec2 shapeMinMaxY = emittorShape->getMinMaxY();
    glm::vec2 shapeMinMaxZ = emittorShape->getMinMaxZ();

    int ParticlesToSpawn = RandomNumberGenerator::getRandomNumber(35, 50);

    for (int i = 0; i < ParticlesToSpawn; i++)
    {
        glm::vec3 newDirection = glm::normalize(glm::vec3(
            RandomNumberGenerator::getRandomNumber(1, 64) * (RandomNumberGenerator::getRandomNumber(0, 1) - 0.5f) * 2.0f,
            RandomNumberGenerator::getRandomNumber(1, 64) * (RandomNumberGenerator::getRandomNumber(0, 1) - 0.5f) * 2.0f,
            RandomNumberGenerator::getRandomNumber(1, 64) * (RandomNumberGenerator::getRandomNumber(0, 1) - 0.5f) * 2.0f));

        glm::vec3 newParticlePos = glm::vec3(0.0f);

        if (emittorShapeType.compare("Point") == 0)
        {
            newParticlePos = glm::vec3(0.0f);
        }

        if (emittorShapeType.compare("Box") == 0)
        {
            newParticlePos = glm::vec3(
                                 RandomNumberGenerator::getRandomDecimal(shapeMinMaxX.x, shapeMinMaxX.y),
                                 RandomNumberGenerator::getRandomDecimal(shapeMinMaxY.x, shapeMinMaxY.y),
                                 RandomNumberGenerator::getRandomDecimal(shapeMinMaxZ.x, shapeMinMaxZ.y)) +
                             this->m_pEmittor->getOffset();
        }

        else if (emittorShape->getShapeType().compare("Sphere") == 0)
        {
            // TO BE ADDED
        }

        float newLifespan = this->m_pEmittor->getParticleBaseLifespan() + static_cast<float>(RandomNumberGenerator::getRandomNumber(0, 128) / 64.0f);

        this->m_pEmittor->activateParticle(
            newParticlePos,
            this->m_pEmittor->getStartScale(),
            newDirection,
            this->m_pEmittor->getDefaultColour(),
            newLifespan);
    }
}
