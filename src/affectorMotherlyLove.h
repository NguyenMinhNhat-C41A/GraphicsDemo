#pragma once

#include "../thirdparty/tinyxml2/tinyxml2.h"

#include "emittor.h"
#include "affector.h"
class Emittor;
class AffectorMotherlyLove : public Affector
{
public:
    //--------------------------------------------------------------------------------
    //
    // PUBLIC METHODS
    //
    //--------------------------------------------------------------------------------

    static Affector *Factory(Emittor *p_pEmittor, tinyxml2::XMLNode *p_pXMLNode);

    ~AffectorMotherlyLove();
    virtual void update(float p_dt) override;

private:
    //--------------------------------------------------------------------------------
    //
    // PRIVATE METHODS
    //
    //--------------------------------------------------------------------------------

    AffectorMotherlyLove(Emittor *p_pEmittor);
    virtual void affect(float p_dt) override;

    //--------------------------------------------------------------------------------
    //
    // PRIVATE VARIABLES
    //
    //--------------------------------------------------------------------------------

    Node *m_pMother = nullptr;
    Node *m_pChildMostDear = nullptr;
};