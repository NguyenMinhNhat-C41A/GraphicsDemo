#pragma once

#include "../wolf/wolf.h"
#include "../thirdparty/tinyxml2/tinyxml2.h"

#include "shape.h"

class ShapePoint : public Shape
{
public:
    //--------------------------------------------------------------------------------
    //
    // PUBLIC METHODS
    //
    //--------------------------------------------------------------------------------

    static Shape *Factory(tinyxml2::XMLNode *p_pXMLNode);

    ~ShapePoint();

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

    ShapePoint();

    //--------------------------------------------------------------------------------
    //
    // PRIVATE VARIABLES
    //
    //--------------------------------------------------------------------------------

    static const std::string s_sShapeType;

    glm::vec3 m_vPoint = glm::vec3(0.0f);
};
