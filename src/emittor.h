#pragma once
#include <iostream>
#include "../thirdparty/tinyxml2/tinyxml2.h"
#include "../wolf/wolf.h"

#include "vertex.h"
#include "transform.h"

#include "componentEffect.h"

#include "shape.h"
#include "shapePoint.h"
#include "shapeBox.h"

#include "emissionMode.h"
#include "emissionModeBurst.h"
#include "emissionModeContinuous.h"

#include "affector.h"
#include "affectorLinearMove.h"
#include "affectorScale.h"
#include "affectorFade.h"

class ComponentEffect;
class EmissionMode;
class Affector;

class Emittor
{
    friend ComponentEffect;

public:
    //--------------------------------------------------------------------------------
    //
    // PARTICLE
    //
    //--------------------------------------------------------------------------------

    class Particle
    {
        friend Emittor;

    public:
        Particle();
        ~Particle();

        void activate();
        void activate(const glm::vec3 &newPos, const glm::vec3 &newScale, const glm::vec3 &newDir, const glm::vec4 &newColour, float newLifespan);

        void update(float p_dt);

        Particle *getNextParticle();

        float getAge();
        float getLifespan();

        glm::vec4 getColour();
        void setColour(const glm::vec4 &newColour);

        Transform *getTransform();

        void scale(const glm::vec3 &p_vNewSc);
        void scaleLinear(const glm::vec3 &p_vNewSc);
        void translate(const glm::vec3 &p_vNewTr);
        void translateOnDirection(float p_fDist);

    private:
        float age = 0.0f;
        float lifespan = 5.0f;

        glm::vec4 colour = glm::vec4(1.0f);
        glm::vec3 translationDirection = glm::vec3(0.0f);

        Transform *transform = new Transform();

        Particle *prevParticle = nullptr;
        Particle *nextParticle = nullptr;
    };

    //--------------------------------------------------------------------------------
    //
    // PARTICLELIST
    //
    //--------------------------------------------------------------------------------

    class ParticlesList
    {
        friend Emittor;

    public:
        ParticlesList();

        ~ParticlesList();

        Particle *getFirstParticle();

        int getParticlesCount();

        // Add to tail of list
        void pushParticle(Particle *p_pParticle);
        // Pop first Particle
        Particle *popParticle();
        // Remove specific Particle
        // If found, remove all linkers & return
        Particle *removeParticle(Particle *p_pParticle);

    private:
        Particle *firstParticle = nullptr;
        Particle *lastParticle = nullptr;

        int particlesCount = 0;
    };

    //--------------------------------------------------------------------------------
    //
    // PUBLIC METHODS
    //
    //--------------------------------------------------------------------------------
    static Emittor *Factory(ComponentEffect *p_pCompFX, tinyxml2::XMLNode *p_pXMLNode);
    void update(float p_dt);
    void render(const glm::mat4 &p_mProj, const glm::mat4 &p_mView);

    void addParticle();

    void activateParticle();
    void activateParticle(const glm::vec3 &newPos, const glm::vec3 &newScale, const glm::vec3 &newDir, const glm::vec4 &newColour, float newLifespan);
    void deactivateParticle();
    void deactivateParticle(Particle *p_pParticle);

    ParticlesList *getActiveParticles();

    Shape *getEmittorShape();

    float getEmittorDuration();
    float getParticleBaseLifespan();

    glm::vec4 getDefaultColour();
    void setDefaultColour(const glm::vec4 &p_vNewColour);
    void setAllParticlesToDefaultColour();

    glm::vec3 getOffset();
    glm::vec3 getStartScale();
    glm::vec3 getEndScale();
    glm::vec3 getDeltaScale();

private:
    //--------------------------------------------------------------------------------
    //
    // PRIVATE METHODS
    //
    //--------------------------------------------------------------------------------

    Emittor(ComponentEffect *compFX);
    ~Emittor();

    //--------------------------------------------------------------------------------
    //
    // PRIVATE VARIABLES
    //
    //--------------------------------------------------------------------------------

    ComponentEffect *m_pCompFX = nullptr;
    Shape *m_pEmittorShape = nullptr;
    EmissionMode *m_pEmissionMode = nullptr;
    std::vector<Affector *> m_vAffectors;

    int m_iNumParticles = 0;
    int m_iNumParticlesCap = 50;
    float m_fParticleBaseLifespan = 1.0f;

    float m_fTimer = 0.0f;
    float m_fEmittorDuration = 1.0f;

    glm::vec3 m_vOffset = glm::vec3(1.0f);
    glm::vec4 m_vDefaultColour = glm::vec4(0.0f, 0.0f, 0.0f, 255.0f);

    glm::vec3 m_vStartScale = glm::vec3(1.0f);
    glm::vec3 m_vEndScale = glm::vec3(1.0f);
    glm::vec3 m_vDeltaScale = glm::vec3(0.0f);

    ParticlesList *m_DormantParticles = nullptr;
    ParticlesList *m_ActiveParticles = nullptr;

    wolf::VertexBuffer *m_pVB = nullptr;
    wolf::VertexDeclaration *m_pDecl = nullptr;
    wolf::Program *m_pProgram = nullptr;

    wolf::Texture *m_pParticleTexture = nullptr;

    QuadVertexColouredTextured m_ParticleVertices[7168];

    static int s_iEmittorCounter;
};