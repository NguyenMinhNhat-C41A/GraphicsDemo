#include "affectorScale.h"

//--------------------------------------------------------------------------------
//
// PUBLIC METHODS
//
//--------------------------------------------------------------------------------

AffectorScale::AffectorScale(Emittor *p_pEmittor) : Affector(p_pEmittor)
{
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

void AffectorScale::affect(float p_dt)
{

    for (auto activeParticle = this->m_pEmittor->getActiveParticles()->getFirstParticle(); activeParticle != nullptr; activeParticle = activeParticle->getNextParticle())
    {
        activeParticle->scaleLinear(this->m_pEmittor->getDeltaScale() * (p_dt / activeParticle->getLifespan()));
        glm::vec3 scale = activeParticle->getTransform()->getScale();
        if (scale.x > this->m_pEmittor->getEndScale().x || scale.y > this->m_pEmittor->getEndScale().y || scale.z > this->m_pEmittor->getEndScale().z)
        {
            std::cout << "AFFSCALE - FIRSTSCALE:X:" << scale.x << "_Y:" << scale.y << "_Z:" << scale.z << "_AGE:" << activeParticle->getAge() << std::endl;
        }
    }
    // Emittor::Particle *firstParticle = this->m_pEmittor->getActiveParticles()->getFirstParticle();
    // if (firstParticle != nullptr)
    // {
    //     glm::vec3 firstScale = firstParticle->getTransform()->getScale();
    //     std::cout << "AFFSCALE - FIRSTSCALE:X:" << firstScale.x << "_Y:" << firstScale.y << "_Z:" << firstScale.z << std::endl;
    //     printf("------------------------------------------------\n");
    // }
}
