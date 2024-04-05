#include "emissionModeContinuous.h"

//--------------------------------------------------------------------------------
//
// PUBLIC METHODS
//
//--------------------------------------------------------------------------------

EmissionModeContinuous::EmissionModeContinuous(Emittor *p_pEmittor) : EmissionMode(p_pEmittor)
{
}

EmissionModeContinuous::~EmissionModeContinuous()
{
}

void EmissionModeContinuous::update(float p_dt)
{
    this->m_pTimer += p_dt;
    this->emit();
}

//--------------------------------------------------------------------------------
//
// PRIVATE METHODS
//
//--------------------------------------------------------------------------------

void EmissionModeContinuous::emit()
{
    int spawnChance = RandomNumberGenerator::getRandomNumber(0, 4);
    if (spawnChance <= 1)
    {
        int ParticlesToSpawn = RandomNumberGenerator::getRandomNumber(1, 2);

        for (int i = 0; i < ParticlesToSpawn; i++)
        {
            // std::cout << "EMIMODECONT - EMIT:" << this->m_pTimer << std::endl;
            glm::vec3 newParticlePos = glm::vec3(
                RandomNumberGenerator::getRandomNumber(0, 2) / 4.0f,
                RandomNumberGenerator::getRandomNumber(0, 2) / 4.0f,
                RandomNumberGenerator::getRandomNumber(0, 2) / 4.0f);

            glm::vec3 newDirection = glm::normalize(glm::vec3(
                RandomNumberGenerator::getRandomNumber(1, 64) * (RandomNumberGenerator::getRandomNumber(0, 1) - 0.5f) * 2.0f,
                RandomNumberGenerator::getRandomNumber(1, 64) * (RandomNumberGenerator::getRandomNumber(0, 1) - 0.5f) * 2.0f,
                RandomNumberGenerator::getRandomNumber(1, 64) * (RandomNumberGenerator::getRandomNumber(0, 1) - 0.5f) * 2.0f));

            this->m_pEmittor->activateParticle(newParticlePos, this->m_pEmittor->getStartScale(), newDirection);
        }
    }
}
