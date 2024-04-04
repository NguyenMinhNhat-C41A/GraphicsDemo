#pragma once
#include <iostream>
#include "../thirdparty/tinyxml2/tinyxml2.h"

#include "vertex.h"
#include "transform.h"
#include "componentEffect.h"
#include "emissionMode.h"
#include "emissionModeContinuous.h"
#include "affector.h"
#include "affectorLinearMove.h"
#include "affectorScale.h"
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
        void activate(const glm::vec3 &newPos, const glm::vec3 &newScale, const glm::vec3 &newDir);

        void update(float p_dt);

        Particle *getNextParticle();

        void scale(const glm::vec3 &p_vNewSc);
        void scaleLinear(const glm::vec3 &p_vNewSc);
        void translate(const glm::vec3 &p_vNewTr);
        void translateOnDirection(float p_fDist);

    private:
        float lifespan = 2.0f;
        float age = 0.0f;

        glm::vec3 translationDirection = glm::vec3(0.0f);

        Transform *transform = new Transform();
        glm::vec4 colour = glm::vec4(0.0f);

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
    void activateParticle(const glm::vec3 &newPos, const glm::vec3 &newScale, const glm::vec3 &newDir);
    void deactivateParticle();
    void deactivateParticle(Particle *p_pParticle);

    ParticlesList *getActiveParticles();

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
    EmissionMode *m_pEmissionMode = nullptr;
    std::vector<Affector *> m_vAffectors;

    int m_iNumParticles = 0;
    int m_iNumParticlesCap = 50;

    float m_fTimer = 0.0f;
    float m_fTestTimer = 0.0f;

    ParticlesList *m_DormantParticles = nullptr;
    ParticlesList *m_ActiveParticles = nullptr;

    wolf::VertexBuffer *m_pVB = nullptr;
    wolf::VertexDeclaration *m_pDecl = nullptr;
    wolf::Program *m_pProgram = nullptr;

    QuadVertex m_ParticleVertices[6144];

    static int s_iEmittorCounter;
};