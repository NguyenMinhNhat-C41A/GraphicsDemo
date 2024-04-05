#pragma once
#include "emittor.h"

#include "affector.h"
class Emittor;
class AffectorFade : public Affector
{
public:
    //--------------------------------------------------------------------------------
    //
    // PUBLIC METHODS
    //
    //--------------------------------------------------------------------------------

    AffectorFade(Emittor *p_pEmittor);
    ~AffectorFade();
    virtual void update(float p_dt) override;

private:
    //--------------------------------------------------------------------------------
    //
    // PRIVATE METHODS
    //
    //--------------------------------------------------------------------------------

    virtual void affect(float p_dt) override;
};