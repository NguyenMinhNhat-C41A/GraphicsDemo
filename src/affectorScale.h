#pragma once
#include "emittor.h"

#include "affector.h"
class Emittor;
class AffectorScale : public Affector
{
public:
    //--------------------------------------------------------------------------------
    //
    // PUBLIC METHODS
    //
    //--------------------------------------------------------------------------------

    AffectorScale(Emittor *p_pEmittor);
    ~AffectorScale();
    virtual void update(float p_dt) override;

private:
    //--------------------------------------------------------------------------------
    //
    // PRIVATE METHODS
    //
    //--------------------------------------------------------------------------------

    virtual void affect(float p_dt) override;
};