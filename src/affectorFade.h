#pragma once

#include "../thirdparty/tinyxml2/tinyxml2.h"

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

    static Affector *Factory(Emittor *p_pEmittor, tinyxml2::XMLNode *p_pXMLNode);

    ~AffectorFade();
    virtual void update(float p_dt) override;

private:
    //--------------------------------------------------------------------------------
    //
    // PRIVATE METHODS
    //
    //--------------------------------------------------------------------------------

    AffectorFade(Emittor *p_pEmittor);
    virtual void affect(float p_dt) override;
};