#include "shapeSphere.h"

const std::string ShapeSphere::s_sShapeType = "Sphere";

//--------------------------------------------------------------------------------
//
// PUBLIC METHODS
//
//--------------------------------------------------------------------------------

Shape *ShapeSphere::Factory(tinyxml2::XMLNode *p_pXMLNode)
{
    ShapeSphere *pShapeSphere = new ShapeSphere();
    tinyxml2::XMLNode *pXMLPropertiesNode = p_pXMLNode->FirstChild();

    while (pXMLPropertiesNode != nullptr)
    {
        std::string propTag = pXMLPropertiesNode->Value();

        if (propTag.compare("Dimensions") == 0)
        {
            float radius = 1.0f;

            if (pXMLPropertiesNode->ToElement()->QueryFloatAttribute("radius", &radius) != tinyxml2::XML_SUCCESS)
            {
                printf("SHAPERAD - DEFAULT_RADIUS\n");
            }

            pShapeSphere->m_fRadius = radius;
        }

        pXMLPropertiesNode = pXMLPropertiesNode->NextSibling();
    }

    return pShapeSphere;
}

ShapeSphere::ShapeSphere()
{
}

ShapeSphere::~ShapeSphere()
{
}

glm::vec2 ShapeSphere::getMinMaxX()
{
    return glm::vec2(-this->m_fRadius, this->m_fRadius);
}

glm::vec2 ShapeSphere::getMinMaxY()
{
    return glm::vec2(-this->m_fRadius, this->m_fRadius);
}

glm::vec2 ShapeSphere::getMinMaxZ()
{
    return glm::vec2(-this->m_fRadius, this->m_fRadius);
}

std::string ShapeSphere::getShapeType()
{
    return s_sShapeType;
}
