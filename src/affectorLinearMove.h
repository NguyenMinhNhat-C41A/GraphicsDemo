#pragma once
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

    AffectorLinearMove(Emittor *p_pEmittor);
    ~AffectorLinearMove();
    virtual void update(float p_dt) override;

private:
    //--------------------------------------------------------------------------------
    //
    // PRIVATE METHODS
    //
    //--------------------------------------------------------------------------------

    virtual void affect(float p_dt) override;
};
