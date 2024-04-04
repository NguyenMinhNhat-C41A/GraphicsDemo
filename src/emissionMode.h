#pragma once

#include "rng.h"

class Emittor;
class EmissionMode
{
public:
    //--------------------------------------------------------------------------------
    //
    // PUBLIC METHODS
    //
    //--------------------------------------------------------------------------------

    ~EmissionMode()
    {
        this->m_pEmittor = nullptr;
    };

    virtual void update(float p_dt) = 0;

protected:
    //--------------------------------------------------------------------------------
    //
    // PROTECTED METHODS
    //
    //--------------------------------------------------------------------------------

    virtual void emit() = 0;

    EmissionMode(Emittor *p_pEmittor)
    {
        this->m_pEmittor = p_pEmittor;
    };

    //--------------------------------------------------------------------------------
    //
    // PROTECTED MEMBER VARIABLES
    //
    //--------------------------------------------------------------------------------

    float m_pTimer = 0.0f;
    Emittor *m_pEmittor = nullptr;
};