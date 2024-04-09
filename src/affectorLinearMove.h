#pragma once

#include "../thirdparty/tinyxml2/tinyxml2.h"

#include "emittor.h"
#include "affector.h"

class Emittor;

class AffectorLinearMove : public Affector
{
public:
    //--------------------------------------------------------------------------------
    //
    // PUBLIC METHODS
    //
    //--------------------------------------------------------------------------------

    static Affector *Factory(Emittor *p_pEmittor, tinyxml2::XMLNode *p_pXMLNode);

    ~AffectorLinearMove();
    virtual void update(float p_dt) override;

private:
    //--------------------------------------------------------------------------------
    //
    // PRIVATE METHODS
    //
    //--------------------------------------------------------------------------------

    virtual void affect(float p_dt) override;

    //--------------------------------------------------------------------------------
    //
    // PRIVATE VARIABLES
    //
    //--------------------------------------------------------------------------------

    AffectorLinearMove(Emittor *p_pEmittor);
    glm::vec3 m_vVelocity = glm::vec3(1.0f);
    bool m_bIsMoveOnParticleDirection = false;
};
