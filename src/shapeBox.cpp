#include "shapeBox.h"

//--------------------------------------------------------------------------------
//
// PUBLIC METHODS
//
//--------------------------------------------------------------------------------

Shape *ShapeBox::Factory(tinyxml2::XMLNode *p_pXMLNode)
{
    ShapeBox *pShapeBox = new ShapeBox();
    tinyxml2::XMLNode *pXMLPropertiesNode = p_pXMLNode->FirstChild();

    while (pXMLPropertiesNode != nullptr)
    {
        std::string propTag = pXMLPropertiesNode->Value();

        if (propTag.compare("Dimensions") == 0)
        {
            float w, h, l = 1.0f;

            if (pXMLPropertiesNode->ToElement()->QueryFloatAttribute("width", &w) != tinyxml2::XML_SUCCESS)
            {
                printf("SHAPEBOX - DEFAULT_WIDTH\n");
            }

            if (pXMLPropertiesNode->ToElement()->QueryFloatAttribute("height", &h) != tinyxml2::XML_SUCCESS)
            {
                printf("SHAPEBOX - DEFAULT_HEIGHT\n");
            }

            if (pXMLPropertiesNode->ToElement()->QueryFloatAttribute("length", &l) != tinyxml2::XML_SUCCESS)
            {
                printf("SHAPEBOX - DEFAULT_LENGTH\n");
            }

            pShapeBox->m_fWidth = w;
            pShapeBox->m_fHeight = h;
            pShapeBox->m_fLength = l;
        }

        pXMLPropertiesNode = pXMLPropertiesNode->NextSibling();
    }
    return pShapeBox;
}

ShapeBox::ShapeBox()
{
}

ShapeBox::~ShapeBox()
{
}

glm::vec2 ShapeBox::getMinMaxX()
{
    float halfWidth = this->m_fWidth * 0.5f;
    return glm::vec2(-halfWidth, halfWidth);
}

glm::vec2 ShapeBox::getMinMaxY()
{
    float halfHeight = this->m_fHeight * 0.5f;
    return glm::vec2(-halfHeight, halfHeight);
}

glm::vec2 ShapeBox::getMinMaxZ()
{
    float halfLength = this->m_fLength * 0.5f;
    return glm::vec2(-halfLength, halfLength);
}

//--------------------------------------------------------------------------------
//
// PRIVATE METHODS
//
//--------------------------------------------------------------------------------