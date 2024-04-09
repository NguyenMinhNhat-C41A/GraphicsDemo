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

    static Shape *Factory(tinyxml2::XMLNode *pXMLNode);
    ShapePoint();
    ~ShapePoint();  

    virtual glm::vec2 getMinMaxX() override;
    virtual glm::vec2 getMinMaxY() override;
    virtual glm::vec2 getMinMaxZ() override;

private:
    //--------------------------------------------------------------------------------
    //
    // PRIVATE METHODS
    //
    //--------------------------------------------------------------------------------
    
    

    glm::vec3 m_vPoint = glm::vec3(0.0f);
};
