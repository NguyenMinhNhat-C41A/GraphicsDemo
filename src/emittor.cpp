#include "emittor.h"

static const QuadVertex s_ParticleVerticesTemplate[] = {

    {0.0f, 0.5f, 0.5f},
    {0.0f, 0.5f, -0.5f},
    {0.0f, -0.5f, -0.5f},
    {0.0f, -0.5f, -0.5f},
    {0.0f, -0.5f, 0.5f},
    {0.0f, 0.5f, 0.5f},
};

int Emittor::s_iEmittorCounter = 0;

//--------------------------------------------------------------------------------
//
// PARTICLE
//
//--------------------------------------------------------------------------------

Emittor::Particle ::Particle()
{
    {
        this->prevParticle = nullptr;
        this->nextParticle = nullptr;
    }
}

Emittor::Particle::~Particle()
{
    this->prevParticle = nullptr;
    this->nextParticle = nullptr;

    delete this->transform;
    this->transform = nullptr;
}

void Emittor::Particle::activate()
{
    this->age = 0.0f;
    this->transform->setTranslate(glm::vec3(0.0f));
    this->transform->setScale(glm::vec3(1.0f));
    this->translationDirection = glm::vec3(0.0f);
}

void Emittor::Particle::activate(const glm::vec3 &newPos, const glm::vec3 &newScale, const glm::vec3 &newDir)
{
    this->age = 0.0f;
    this->transform->setTranslate(newPos);
    this->transform->setScale(newScale);
    this->translationDirection = newDir;
}
void Emittor::Particle::update(float p_dt)
{
    this->age += p_dt;
}

Emittor::Particle *Emittor::Particle::getNextParticle()
{
    return this->nextParticle;
}

void Emittor::Particle::scale(const glm::vec3 &p_vNewSc)
{
    this->transform->setScale(this->transform->getScale() * p_vNewSc);
}

void Emittor::Particle::scaleLinear(const glm::vec3 &p_vNewSc)
{
    glm::vec3 newScale = this->transform->getScale() + p_vNewSc;
    if (newScale.x > 0 && newScale.y > 0 && newScale.z > 0)
    {
        this->transform->setScale(newScale);
    }
}

void Emittor::Particle::translate(const glm::vec3 &p_vNewTr)
{
    this->transform->setTranslate(this->transform->getTranslate() + p_vNewTr);
}

void Emittor::Particle::translateOnDirection(float p_fDist)
{
    this->transform->setTranslate(this->transform->getTranslate() + this->translationDirection * p_fDist);
}

//--------------------------------------------------------------------------------
//
// PARTICLESLIST
//
//--------------------------------------------------------------------------------

Emittor::ParticlesList::ParticlesList()
{
    this->firstParticle = nullptr;
    this->lastParticle = nullptr;

    this->particlesCount = 0;
}

Emittor::ParticlesList::~ParticlesList()
{
    for (auto particle = this->firstParticle; particle != nullptr; particle = particle->nextParticle)
    {
        delete particle;
        particle = nullptr;
    }

    this->firstParticle = nullptr;
    this->lastParticle = nullptr;
}

Emittor::Particle *Emittor::ParticlesList::getFirstParticle()
{
    return this->firstParticle;
}

int Emittor::ParticlesList::getParticlesCount()
{
    return this->particlesCount;
}

void Emittor::ParticlesList::pushParticle(Particle *p_pParticle)
{
    if (this->particlesCount == 0)
    {
        this->firstParticle = p_pParticle;
        this->lastParticle = this->firstParticle;
        this->particlesCount++;
        // printf("EMITTOR - PATICLE:ADD_C1:%d\n", this->particlesCount);
        return;
    }
    this->lastParticle->nextParticle = p_pParticle;
    this->lastParticle->nextParticle->prevParticle = this->lastParticle;
    this->lastParticle = this->lastParticle->nextParticle;
    this->particlesCount++;
    // printf("EMITTOR - PATICLE:ADD_C2:%d\n", this->particlesCount);
    return;
}

Emittor::Particle *Emittor::ParticlesList::popParticle()
{
    Particle *returnParticle = nullptr;
    if (this->particlesCount == 0)
    {
        std::cout << "EMITTOR - POP_ERROR:LIST_EMPTY" << std::endl;
    }

    else
    {
        returnParticle = this->firstParticle;
        if (this->particlesCount == 1)
        {
            this->firstParticle = nullptr;
            this->lastParticle = nullptr;
        }
        else
        {

            this->firstParticle = this->firstParticle->nextParticle;
            this->firstParticle->prevParticle->nextParticle = nullptr;
            this->firstParticle->prevParticle = nullptr;
        }
        this->particlesCount--;
    }
    return returnParticle;
}

Emittor::Particle *Emittor::ParticlesList::removeParticle(Particle *p_pParticle)
{
    if (this->particlesCount == 0)
    {
        std::cout << "EMITTOR - REMOVE_ERROR:LIST_EMPTY" << std::endl;
        return nullptr;
    }
    else
    {
        if (this->particlesCount == 1)
        {
            if (this->firstParticle == p_pParticle)
            {
                Particle *returnParticle = this->firstParticle;

                this->firstParticle = nullptr;
                this->lastParticle = nullptr;
                this->particlesCount--;

                return returnParticle;
            }
            else
            {
                std::cout << "EMITTOR - REMOVE_ERROR:PARTICLE_NOT_FOUND" << std::endl;
                return nullptr;
            }
        }

        else
        {
            Particle *currentParticle = this->firstParticle;
            while (currentParticle != nullptr)
            {
                if (currentParticle == p_pParticle)
                {
                    // If current Particle is not first Particle
                    if (currentParticle->prevParticle != nullptr)
                    {
                        currentParticle->prevParticle->nextParticle = currentParticle->nextParticle;
                    }
                    else
                    {
                        this->firstParticle = this->firstParticle->nextParticle;
                    }

                    // If current Particle is not last Particle
                    if (currentParticle->nextParticle != nullptr)
                    {
                        currentParticle->nextParticle->prevParticle = currentParticle->prevParticle;
                    }
                    else
                    {
                        this->lastParticle = this->lastParticle->prevParticle;
                    }

                    // Removing linkers from current Particle
                    currentParticle->nextParticle = nullptr;
                    currentParticle->prevParticle = nullptr;

                    this->particlesCount--;
                    return currentParticle;
                }
                currentParticle = currentParticle->nextParticle;
            }
            std::cout << "EMITTOR - REMOVE_ERROR:PARTICLE_NOT_FOUND" << std::endl;
            return nullptr;
        }
    }
}

//--------------------------------------------------------------------------------
//
// PUBLIC METHODS
//
//--------------------------------------------------------------------------------

Emittor *Emittor::Factory(ComponentEffect *p_pCompFX, tinyxml2::XMLNode *p_pXMLNode)
{
    Emittor *emittor = new Emittor(p_pCompFX);
    EmissionMode *emissionMode = nullptr;
    std::string emmo = "";
    std::string aff = "";
    tinyxml2::XMLNode *pXMLPropertiesNode = p_pXMLNode->FirstChild();

    while (pXMLPropertiesNode != nullptr)
    {

        std::string propTag = pXMLPropertiesNode->Value();

        //-----------------------------------
        // PARTICLE
        //-----------------------------------
        if (propTag.compare("Particle") == 0)
        {
            float particleLifespan = 1.0f;

            if (pXMLPropertiesNode->ToElement()->QueryFloatAttribute("lifespan", &particleLifespan) != tinyxml2::XML_SUCCESS)
            {
                printf("EMITTOR - ERROR:DATA_NOT_FOUND:LIFESPAN\n");
            }
            emittor->m_fParticleLifespan = particleLifespan;
        }
        //-----------------------------------
        // EMISSION MODE
        //-----------------------------------

        else if (propTag.compare("EmissionMode") == 0)
        {
            if (emissionMode == nullptr)
            {
                emmo = pXMLPropertiesNode->ToElement()->Attribute("mode");
                if (emmo.compare("continuous") == 0)
                {
                    emissionMode = new EmissionModeContinuous(emittor);
                    emittor->m_pEmissionMode = emissionMode;
                }
            }
        }

        //-----------------------------------
        // AFFECTOR
        //-----------------------------------

        else if (propTag.compare("Affector") == 0)
        {
            aff = pXMLPropertiesNode->ToElement()->Attribute("type");
            if (aff.compare("linearMove") == 0)
            {
                emittor->m_vAffectors.push_back(new AffectorLinearMove(emittor));
            }
            else if (aff.compare("scale") == 0)
            {
                emittor->m_vAffectors.push_back(new AffectorScale(emittor));
                glm::vec3 startScale, endScale = glm::vec3(1.0f);

                // START SCALE
                if (pXMLPropertiesNode->ToElement()->QueryFloatAttribute("startX", &startScale.x) != tinyxml2::XML_SUCCESS)
                {
                    printf("EMITTOR - DEFAULT_START_SCALE_X\n");
                }

                if (pXMLPropertiesNode->ToElement()->QueryFloatAttribute("startY", &startScale.y) != tinyxml2::XML_SUCCESS)
                {
                    printf("EMITTOR - DEFAULT_START_SCALE_Y\n");
                }

                if (pXMLPropertiesNode->ToElement()->QueryFloatAttribute("startZ", &startScale.z) != tinyxml2::XML_SUCCESS)
                {
                    printf("EMITTOR - DEFAULT_START_SCALE_Z\n");
                }

                // END SCALE
                if (pXMLPropertiesNode->ToElement()->QueryFloatAttribute("endX", &endScale.x) != tinyxml2::XML_SUCCESS)
                {
                    printf("EMITTOR - DEFAULT_END_SCALE_X\n");
                }

                if (pXMLPropertiesNode->ToElement()->QueryFloatAttribute("endY", &endScale.y) != tinyxml2::XML_SUCCESS)
                {
                    printf("EMITTOR - DEFAULT_END_SCALE_Y\n");
                }

                if (pXMLPropertiesNode->ToElement()->QueryFloatAttribute("endZ", &endScale.z) != tinyxml2::XML_SUCCESS)
                {
                    printf("EMITTOR - DEFAULT_END_SCALE_Z\n");
                }

                emittor->m_vStartScale = startScale;
                emittor->m_vEndScale = endScale;
                emittor->m_vDeltaScale = endScale - startScale;
            }
        }

        pXMLPropertiesNode = pXMLPropertiesNode->NextSibling();
    }

    //-----------------------------------
    // SETTING DEFAULTS
    //-----------------------------------
    if (emissionMode == nullptr)
    {

        printf("EMITTOR - SET_DEFAULT_EMISSION_MODE\n");
        emissionMode = new EmissionModeContinuous(emittor);
        emittor->m_pEmissionMode = emissionMode;
    }

    if (emittor->m_vAffectors.size() == 0)
    {
        printf("EMITTOR - SET_DEFAULT_AFFECTOR\n");
        emittor->m_vAffectors.push_back(new AffectorLinearMove(emittor));
    }

    return emittor;
}

void Emittor::update(float p_dt)
{
    this->m_fTimer += p_dt;
    this->m_fTestTimer += p_dt;

    Particle *currentActiveParticle = this->m_ActiveParticles->firstParticle;

    this->m_pEmissionMode->update(p_dt);
    for (auto affector : this->m_vAffectors)
    {
        affector->update(p_dt);
    }

    while (currentActiveParticle != nullptr)
    {
        currentActiveParticle->update(p_dt);
        if (currentActiveParticle->age >= this->m_fParticleLifespan)
        {
            // std::cout << "EMITTOR - DEACTIVATE_PARTICLE" << std::endl;
            this->deactivateParticle(currentActiveParticle);
        }

        currentActiveParticle = currentActiveParticle->nextParticle;
    }
    currentActiveParticle = nullptr;
}

void Emittor::render(const glm::mat4 &p_mProj, const glm::mat4 &p_mView)
{
    m_pProgram->SetUniform("view", p_mProj * p_mView);
    m_pProgram->SetUniform("world", glm::mat4(1.0f));
    m_pProgram->SetUniform("colour", glm::vec4(0.0f, 144.0f, 48.0f, 1.0f));
    m_pProgram->Bind();
    m_pDecl->Bind();

    // Camera-related
    glm::vec3 camRight = glm::vec3(p_mView[0][0], p_mView[1][0], p_mView[2][0]);
    glm::vec3 camUp = glm::vec3(p_mView[0][1], p_mView[1][1], p_mView[2][1]);
    // Positions
    glm::vec3 glmEmittorPos = this->m_pCompFX->getGlobalTranslate();
    QuadVertex currentEmittorPosition;
    currentEmittorPosition.x = glmEmittorPos.x;
    currentEmittorPosition.y = glmEmittorPos.y;
    currentEmittorPosition.z = glmEmittorPos.z;

    // Updating vertex array
    int i = 0;

    for (auto currentActiveParticle = this->m_ActiveParticles->firstParticle; currentActiveParticle != nullptr; currentActiveParticle = currentActiveParticle->nextParticle)
    {
        for (int j = 0; j < 6; j++)
        {
            glm::vec3 newVPos = (currentActiveParticle->transform->getTranslate() +
                                 s_ParticleVerticesTemplate[j].y * camRight * currentActiveParticle->transform->getScale().x +
                                 s_ParticleVerticesTemplate[j].z * camUp * currentActiveParticle->transform->getScale().y);

            this->m_ParticleVertices[i + j].x = newVPos.x;
            this->m_ParticleVertices[i + j].y = newVPos.y;
            this->m_ParticleVertices[i + j].z = newVPos.z;
        }
        i += 6;
        if (i > this->m_ActiveParticles->particlesCount * 6)
        {
            break;
        }
    }
    glBufferData(GL_ARRAY_BUFFER, sizeof(QuadVertex) * this->m_ActiveParticles->particlesCount * 6, this->m_ParticleVertices, GL_DYNAMIC_DRAW);
    glDrawArrays(GL_TRIANGLES, 0, this->m_ActiveParticles->particlesCount * 6);
    // printf("EMITTOR - NUM_ACTIVE_PARTICLES:%d\n", this->m_ActiveParticles->particlesCount);
}

void Emittor::addParticle()
{
    this->m_DormantParticles->pushParticle(new Particle());
}

void Emittor::activateParticle()
{
    Particle *particle = nullptr;
    if (this->m_DormantParticles->particlesCount == 0)
    {
        particle = this->m_ActiveParticles->popParticle();
        this->m_ActiveParticles->pushParticle(particle);
    }
    else
    {
        particle = this->m_DormantParticles->popParticle();
        this->m_ActiveParticles->pushParticle(particle);
    }

    glm::vec3 glmEmittorPos = this->m_pCompFX->getGlobalTranslate();

    particle->activate();
    return;
}

void Emittor::activateParticle(const glm::vec3 &newPos, const glm::vec3 &newScale, const glm::vec3 &newDir)
{
    Particle *particle = nullptr;
    if (this->m_DormantParticles->particlesCount == 0)
    {
        particle = this->m_ActiveParticles->popParticle();
        this->m_ActiveParticles->pushParticle(particle);
    }
    else
    {
        particle = this->m_DormantParticles->popParticle();
        this->m_ActiveParticles->pushParticle(particle);
    }

    glm::vec3 glmEmittorPos = this->m_pCompFX->getGlobalTranslate();
    glm::vec3 newParticlePos = glmEmittorPos + newPos;

    particle->activate(newParticlePos, newScale, newDir);
}

void Emittor::deactivateParticle()
{
    Particle *particle = nullptr;
    if (this->m_ActiveParticles->particlesCount == 0)
    {
        return;
    }
    else
    {
        particle = this->m_ActiveParticles->popParticle();
        this->m_DormantParticles->pushParticle(particle);
    }

    return;
}

void Emittor::deactivateParticle(Particle *p_pParticle)
{
    Particle *particle = nullptr;
    if (this->m_ActiveParticles->particlesCount == 0)
    {
        return;
    }
    else
    {
        particle = this->m_ActiveParticles->removeParticle(p_pParticle);
        this->m_DormantParticles->pushParticle(particle);
        return;
    }
}

Emittor::ParticlesList *Emittor::getActiveParticles()
{
    return this->m_ActiveParticles;
}

glm::vec3 Emittor::getStartScale()
{
    return this->m_vStartScale;
}

glm::vec3 Emittor::getEndScale()
{
    return this->m_vEndScale;
}

glm::vec3 Emittor::getDeltaScale()
{
    return this->m_vDeltaScale;
}

//--------------------------------------------------------------------------------
//
// PRIVATE METHODS
//
//--------------------------------------------------------------------------------

Emittor::Emittor(ComponentEffect *compFX)
{
    s_iEmittorCounter++;

    this->m_pCompFX = compFX;

    this->m_iNumParticles = 0;
    this->m_iNumParticlesCap = 512;

    this->m_fTimer = 0.0f;

    if (!this->m_pProgram)
    {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        this->m_pProgram = wolf::ProgramManager::CreateProgram("data/particle.vsh", "data/particle.fsh");
        this->m_pVB = wolf::BufferManager::CreateVertexBuffer(this->m_ParticleVertices, sizeof(QuadVertex) * 6, true);

        this->m_pDecl = new wolf::VertexDeclaration();
        this->m_pDecl->Begin();
        this->m_pDecl->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
        this->m_pDecl->SetVertexBuffer(this->m_pVB);
        this->m_pDecl->End();
    }

    this->m_DormantParticles = new ParticlesList();
    this->m_ActiveParticles = new ParticlesList();

    for (int i = 0; i < this->m_iNumParticlesCap; i++)
    {

        this->addParticle();
    }

    this->m_iNumParticles = m_iNumParticlesCap;
}

Emittor::~Emittor()
{
    this->m_pCompFX = nullptr;

    delete this->m_pEmissionMode;
    this->m_pEmissionMode = nullptr;

    for (auto affector : this->m_vAffectors)
    {
        delete affector;
        affector = nullptr;
    }
    this->m_vAffectors.clear();

    delete this->m_DormantParticles;
    this->m_DormantParticles = nullptr;

    delete this->m_ActiveParticles;
    this->m_ActiveParticles = nullptr;

    s_iEmittorCounter--;
    if (s_iEmittorCounter == 0)
    {
        delete this->m_pDecl;
        this->m_pDecl = nullptr;
        wolf::ProgramManager::DestroyProgram(this->m_pProgram);
        this->m_pProgram = nullptr;
        wolf::BufferManager::DestroyBuffer(this->m_pVB);
        this->m_pVB = nullptr;
    }
}