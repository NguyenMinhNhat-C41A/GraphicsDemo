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

    EmissionModeContinuous(Emittor *p_pEmittor);
    ~EmissionModeContinuous();

    virtual void update(float p_dt) override;

private:
    //--------------------------------------------------------------------------------
    //
    // PRIVATE METHODS
    //
    //--------------------------------------------------------------------------------

    virtual void emit() override;
    float m_fEmissionDelay = 2.0f;
};