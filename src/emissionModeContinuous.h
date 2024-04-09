#pragma once

#include "../thirdparty/tinyxml2/tinyxml2.h"

#include "emittor.h"
#include "emissionMode.h"
class Emittor;

class EmissionModeContinuous : public EmissionMode
{
public:
    //--------------------------------------------------------------------------------
    //
    // PUBLIC METHODS
    //
    //--------------------------------------------------------------------------------

    static EmissionMode *Factory(Emittor *p_pEmittor, tinyxml2::XMLNode *p_pXMLNode);

    ~EmissionModeContinuous();

    virtual void update(float p_dt) override;

private:
    //--------------------------------------------------------------------------------
    //
    // PRIVATE METHODS
    //
    //--------------------------------------------------------------------------------

    EmissionModeContinuous(Emittor *p_pEmittor);
    virtual void emit() override;
    
    //--------------------------------------------------------------------------------
    //
    // PRIVATE VARIABLES
    //
    //-------------------------------------------------------------------------------

    float m_fDurationTimer = 0.0f;
    float m_fEmissionDelay = 2.0f;
};