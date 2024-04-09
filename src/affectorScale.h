#pragma once

#include "../thirdparty/tinyxml2/tinyxml2.h"

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

    static Affector *Factory(Emittor *p_pEmittor, tinyxml2::XMLNode *p_pXMLNode);

    ~AffectorScale();
    virtual void update(float p_dt) override;

private:
    //--------------------------------------------------------------------------------
    //
    // PRIVATE METHODS
    //
    //--------------------------------------------------------------------------------
    
    AffectorScale(Emittor *p_pEmittor);

    virtual void affect(float p_dt) override;
    glm::vec3 startScale = glm::vec3(1.0f);
    glm::vec3 endScale = glm::vec3(1.0f);
};