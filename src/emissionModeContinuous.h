#pragma once

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
};