#include "shapePoint.h"

//--------------------------------------------------------------------------------
//
// PUBLIC METHODS
//
//--------------------------------------------------------------------------------

Shape *ShapePoint::Factory(tinyxml2::XMLNode *p_pXMLNode)
{
    ShapePoint *pShapePoint = new ShapePoint();
    return pShapePoint;
}

ShapePoint::~ShapePoint()
{
}

glm::vec2 ShapePoint::getMinMaxX()
{
    return glm::vec2(this->m_vPoint.x);
}

glm::vec2 ShapePoint::getMinMaxY()
{

    return glm::vec2(this->m_vPoint.y);
}

glm::vec2 ShapePoint::getMinMaxZ()
{

    return glm::vec2(this->m_vPoint.z);
}

//--------------------------------------------------------------------------------
//
// PRIVATE METHODS
//
//--------------------------------------------------------------------------------

ShapePoint::ShapePoint()
{
}