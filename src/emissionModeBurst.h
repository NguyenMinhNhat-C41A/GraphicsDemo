#pragma once

#include "../thirdparty/tinyxml2/tinyxml2.h"

#include "emittor.h"
#include "emissionMode.h"

class Emittor;

class EmissionModeBurst : public EmissionMode
{
public:
    //--------------------------------------------------------------------------------
    //
    // PUBLIC METHODS
    //
    //--------------------------------------------------------------------------------
    static EmissionMode *Factory(Emittor *p_pEmittor, tinyxml2::XMLNode *p_pXMLNode);
    EmissionModeBurst(Emittor *p_pEmittor);
    ~EmissionModeBurst();

    virtual void update(float p_dt) override;

private:
    //--------------------------------------------------------------------------------
    //
    // PRIVATE METHODS
    //
    //--------------------------------------------------------------------------------

    virtual void emit() override;

    //--------------------------------------------------------------------------------
    //
    // PRIVATE VARIABLES
    //
    //--------------------------------------------------------------------------------
    float m_fEmissionDelay = 2.0f;
};