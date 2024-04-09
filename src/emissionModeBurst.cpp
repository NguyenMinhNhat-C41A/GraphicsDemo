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

    int ParticlesToSpawn = RandomNumberGenerator::getRandomNumber(35, 50);

    for (int i = 0; i < ParticlesToSpawn; i++)
    {
        // std::cout << "EMIMODECONT - EMIT:" << this->m_pTimer << std::endl;
        glm::vec3 newParticlePos = glm::vec3(
                                       RandomNumberGenerator::getRandomNumber(0, 2) / 4.0f,
                                       RandomNumberGenerator::getRandomNumber(0, 2) / 4.0f,
                                       RandomNumberGenerator::getRandomNumber(0, 2) / 4.0f) +
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
}
