#include "dynamicDebugCube.h"

Node *DynamicDebugCube::Factory(tinyxml2::XMLNode *p_xmlNode)
{
    DynamicDebugCube *ddbc = nullptr;
    std::string name = "DynamicDebugCube" + std::to_string(s_iNodeCount);
    glm::vec3 scale = glm::vec3(1.0f);
    glm::vec3 rotation = glm::vec3(0.0f);
    glm::vec3 translation = glm::vec3(0.0f);

    std::vector<ComponentBase *> components;

    tinyxml2::XMLNode *pXMLPropCompNode = p_xmlNode->FirstChild();
    while (pXMLPropCompNode != nullptr)
    {

        std::string tag = pXMLPropCompNode->Value();
        // std::cout << "DYDEBCUBE - TAG:" << tag << std::endl;

        //-----------------------------------
        // QUERY PROPERTIES
        //-----------------------------------

        if (tag.compare("Properties") == 0)
        {
            tinyxml2::XMLNode *pXMLPropNode = pXMLPropCompNode->FirstChild();

            while (pXMLPropNode != nullptr)
            {
                std::string propTag = pXMLPropNode->Value();

                // std::cout << "DYDEBCUBE - PROPTAG:" << propTag << std::endl;

                //-----------------------------------
                // SCALE
                //-----------------------------------
                if (propTag.compare("Scale") == 0)
                {
                    float scX, scY, scZ = 0.0f;
                    bool random = false;
                    tinyxml2::XMLElement *propElement = pXMLPropNode->ToElement();
                    tinyxml2::XMLError queryResultRandom = propElement->QueryBoolAttribute("random", &random);

                    if (queryResultRandom == tinyxml2::XML_SUCCESS && random)
                    {
                        // printf("DYDEBCUBE - SCALE_RANDOM\n");
                        int rangeLower = 1;
                        int rangeUpper = 7;
                        scale = glm::vec3(
                            RandomNumberGenerator::getRandomNumber(rangeLower, rangeUpper),
                            RandomNumberGenerator::getRandomNumber(rangeLower, rangeUpper),
                            RandomNumberGenerator::getRandomNumber(rangeLower, rangeUpper));
                    }
                    else
                    {
                        if (propElement->QueryFloatAttribute("x", &scX) != tinyxml2::XML_SUCCESS)
                        {
                            std::cerr << "DYDEBCUBE - ERROR:DATA_NOT_FOUND:SC_X" << std::endl;
                        }

                        if (propElement->QueryFloatAttribute("y", &scY) != tinyxml2::XML_SUCCESS)
                        {
                            std::cerr << "DYDEBCUBE - ERROR:DATA_NOT_FOUND:SC_Y" << std::endl;
                        }

                        if (propElement->QueryFloatAttribute("z", &scZ) != tinyxml2::XML_SUCCESS)
                        {
                            std::cerr << "DYDEBCUBE - ERROR:DATA_NOT_FOUND:SC_Z" << std::endl;
                        }

                        // std::cout << "DYDEBCUBE - SCX:" << scX << " - SCY:" << scY << " - SCZ:" << scZ << std::endl;

                        scale = glm::vec3(scX, scY, scZ);
                    }
                }

                //-----------------------------------
                // ROTATION
                //-----------------------------------

                else if (propTag.compare("Rotation") == 0)
                {
                    float roX, roY, roZ = 0.0f;
                    bool random = false;
                    tinyxml2::XMLElement *propElement = pXMLPropNode->ToElement();
                    tinyxml2::XMLError queryResultRandom = propElement->QueryBoolAttribute("random", &random);

                    if (queryResultRandom == tinyxml2::XML_SUCCESS && random)
                    {
                        // printf("DYDEBCUBE - ROTATION_RANDOM\n");
                        int rangeLower = 0;
                        int rangeUpper = 359;
                        rotation = glm::vec3(
                            RandomNumberGenerator::getRandomNumber(rangeLower, rangeUpper),
                            RandomNumberGenerator::getRandomNumber(rangeLower, rangeUpper),
                            RandomNumberGenerator::getRandomNumber(rangeLower, rangeUpper));
                    }
                    else
                    {
                        if (propElement->QueryFloatAttribute("x", &roX) != tinyxml2::XML_SUCCESS)
                        {
                            std::cerr << "DYDEBCUBE - ERROR:DATA_NOT_FOUND:RO_X" << std::endl;
                        }

                        if (propElement->QueryFloatAttribute("y", &roY) != tinyxml2::XML_SUCCESS)
                        {
                            std::cerr << "DYDEBCUBE - ERROR:DATA_NOT_FOUND:RO_Y" << std::endl;
                        }

                        if (propElement->QueryFloatAttribute("z", &roZ) != tinyxml2::XML_SUCCESS)
                        {
                            std::cerr << "DYDEBCUBE - ERROR:DATA_NOT_FOUND:RO_Z" << std::endl;
                        }

                        // std::cout << "DYDEBCUBE - ROX:" << roX << " - ROY:" << roY << " - ROZ:" << roZ << std::endl;

                        rotation = glm::vec3(roX, roY, roZ);
                    }
                }

                //-----------------------------------
                // TRANSLATION
                //-----------------------------------

                else if (propTag.compare("Translation") == 0)
                {
                    float trX, trY, trZ = 0.0f;
                    bool random = false;
                    tinyxml2::XMLElement *propElement = pXMLPropNode->ToElement();
                    tinyxml2::XMLError queryResultRandom = propElement->QueryBoolAttribute("random", &random);

                    if (queryResultRandom == tinyxml2::XML_SUCCESS && random)
                    {
                        // printf("DYDEBCUBE - TRANSLATION_RANDOM\n");
                        int rangeLower = -128;
                        int rangeUpper = 128;
                        translation = glm::vec3(
                            RandomNumberGenerator::getRandomNumber(rangeLower, rangeUpper),
                            RandomNumberGenerator::getRandomNumber(rangeLower, rangeUpper),
                            RandomNumberGenerator::getRandomNumber(rangeLower, rangeUpper));
                    }
                    else
                    {
                        if (propElement->QueryFloatAttribute("x", &trX) != tinyxml2::XML_SUCCESS)
                        {
                            std::cerr << "DYDEBCUBE - ERROR:DATA_NOT_FOUND:TR_X" << std::endl;
                        }

                        if (propElement->QueryFloatAttribute("y", &trY) != tinyxml2::XML_SUCCESS)
                        {
                            std::cerr << "DYDEBCUBE - ERROR:DATA_NOT_FOUND:TR_Y" << std::endl;
                        }

                        if (propElement->QueryFloatAttribute("z", &trZ) != tinyxml2::XML_SUCCESS)
                        {
                            std::cerr << "DYDEBCUBE - ERROR:DATA_NOT_FOUND:TR_Z" << std::endl;
                        }

                        // std::cout << "DYDEBCUBE - TRX:" << trX << " - TRY:" << trY << " - TRZ:" << trZ << std::endl;

                        translation = glm::vec3(trX, trY, trZ);
                    }
                }

                pXMLPropNode = pXMLPropNode->NextSibling();
            }
        }

        //-----------------------------------
        // QUERY COMPONENTS
        //-----------------------------------

        else
        {
            ComponentBase *component = FactoryMethodsManager::Instance()->createComponent(ddbc, pXMLPropCompNode);
            if (component != nullptr)
            {
                components.push_back(component);
            }
        }

        pXMLPropCompNode = pXMLPropCompNode->NextSibling();
    }

    ddbc = new DynamicDebugCube(name, scale, rotation, translation);
    for (auto component : components)
    {
        ddbc->addComponent(component);
    }

    components.clear();

    return ddbc;
}

DynamicDebugCube::DynamicDebugCube() : DebugCube("DynamicDebugCube" + std::to_string(s_iNodeCount), glm::vec3(1.0f), glm::vec3(0.0f), glm::vec3(0.0f))
{
    this->m_fOrbitRadius = glm::length(this->getGlobalTranslate());
    this->yPos = 0.0f;
    this->m_vRotOffset = glm::vec3(0.0f);
    this->m_vTrlOffset = glm::vec3(0.0f);
    this->m_fOrbitDir = 1.0f;
    this->m_vRotDir = glm::vec3(1.0f);
}

DynamicDebugCube::DynamicDebugCube(std::string p_newName, const glm::vec3 &p_vNewSc, const glm::vec3 &p_vNewRo, const glm::vec3 &p_vNewTr) : DebugCube(p_newName, p_vNewSc, p_vNewRo, p_vNewTr)
{
    this->m_fOrbitRadius = glm::length(this->getGlobalTranslate());
    this->yPos = p_vNewTr.y;
    this->m_vRotOffset = p_vNewRo;
    this->m_vTrlOffset = p_vNewTr;
    this->m_fOrbitDir = RandomNumberGenerator::getRandomNumber(0, 1) - 0.5f * 2.0f;
    printf("DYDEBCUBE - ORBITDIR:%2f\n", this->m_fOrbitDir);
    this->m_vRotDir = glm::vec3(
        (RandomNumberGenerator::getRandomNumber(0, 1) - 0.5f) * 2.0f,
        (RandomNumberGenerator::getRandomNumber(0, 1) - 0.5f) * 2.0f,
        (RandomNumberGenerator::getRandomNumber(0, 1) - 0.5f) * 2.0f);
}

DynamicDebugCube::~DynamicDebugCube()
{
}

void DynamicDebugCube::update(float p_dt)
{
    DebugCube::update(p_dt);
    this->m_fCounter += p_dt;

    this->setTranslate(this->m_vTrlOffset +
                       glm::vec3(
                           this->m_fOrbitRadius * glm::sin(this->m_fCounter * this->m_fOrbitSpeed),
                           0.0f,
                           this->m_fOrbitRadius * glm::cos(this->m_fCounter * this->m_fOrbitSpeed)));

    this->setRotate(this->getRotate() + this->m_vRotDir * p_dt * this->m_fRotateSpeed);
}