#pragma once

#include "emittor.h"

class Emittor;

class Affector
{
public:
    //--------------------------------------------------------------------------------
    //
    // PUBLIC METHODS
    //
    //--------------------------------------------------------------------------------

    ~Affector()
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

    Affector(Emittor *p_pEmittor)
    {
        this->m_pEmittor = p_pEmittor;
    };
    virtual void affect(float p_dt) = 0;

    //--------------------------------------------------------------------------------
    //
    // PROTECTED MEMBER VARIABLES
    //
    //--------------------------------------------------------------------------------

    Emittor *m_pEmittor = nullptr;
    float m_pTimer = 0.0f;
};