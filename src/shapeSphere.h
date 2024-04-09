#pragma once

#include "../wolf/wolf.h"
#include "../thirdparty/tinyxml2/tinyxml2.h"

#include "shape.h"

class ShapeSphere : public Shape
{
public:
    //--------------------------------------------------------------------------------
    //
    // PUBLIC METHODS
    //
    //--------------------------------------------------------------------------------

    static Shape *Factory(tinyxml2::XMLNode *p_pXMLNode);

    ~ShapeSphere();

    virtual glm::vec2 getMinMaxX() override;
    virtual glm::vec2 getMinMaxY() override;
    virtual glm::vec2 getMinMaxZ() override;
    virtual std::string getShapeType() override;

private:
    //--------------------------------------------------------------------------------
    //
    // PRIVATE METHODS
    //
    //--------------------------------------------------------------------------------
    ShapeSphere();

    //--------------------------------------------------------------------------------
    //
    // PRIVATE VARIABLES
    //
    //--------------------------------------------------------------------------------

    static const std::string s_sShapeType;

    float m_fRadius = 1.0f;
};