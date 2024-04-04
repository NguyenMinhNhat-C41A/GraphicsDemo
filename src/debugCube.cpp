#include "debugCube.h"
const CubeVertex gs_cubeVertexCoords[] = {
    // ClounterClockwise from Upper Left

    {-0.5f, 0.5f, -0.5f},
    {-0.5f, 0.5f, 0.5f},
    {0.5f, 0.5f, 0.5f},
    {0.5f, 0.5f, 0.5f},
    {0.5f, 0.5f, -0.5f},
    {-0.5f, 0.5f, -0.5f},

    {-0.5f, -0.5f, -0.5f},
    {-0.5f, -0.5f, 0.5f},
    {0.5f, -0.5f, 0.5f},
    {0.5f, -0.5f, 0.5f},
    {0.5f, -0.5f, -0.5f},
    {-0.5f, -0.5f, -0.5f},

    {-0.5f, 0.5f, -0.5f},
    {-0.5f, -0.5f, -0.5f},
    {-0.5f, -0.5f, 0.5f},
    {-0.5f, -0.5f, 0.5f},
    {-0.5f, 0.5f, 0.5f},
    {-0.5f, 0.5f, -0.5f},

    {0.5f, 0.5f, 0.5f},
    {0.5f, -0.5f, 0.5f},
    {0.5f, -0.5f, -0.5f},
    {0.5f, -0.5f, -0.5f},
    {0.5f, 0.5f, -0.5f},
    {0.5f, 0.5f, 0.5f},

    {-0.5f, 0.5f, 0.5f},
    {-0.5f, -0.5f, 0.5f},
    {0.5f, -0.5f, 0.5f},
    {0.5f, -0.5f, 0.5f},
    {0.5f, 0.5f, 0.5f},
    {-0.5f, 0.5f, 0.5f},

    {-0.5f, 0.5f, -0.5f},
    {-0.5f, -0.5f, -0.5f},
    {0.5f, -0.5f, -0.5f},
    {0.5f, -0.5f, -0.5f},
    {0.5f, 0.5f, -0.5f},
    {-0.5f, 0.5f, -0.5f},
};

int DebugCube::cubeCounter = 0;

wolf::VertexBuffer *DebugCube::s_pVB = nullptr;
wolf::VertexDeclaration *DebugCube::s_pDecl = nullptr;
wolf::Program *DebugCube::s_pProgram = nullptr;

Node *DebugCube::Factory(tinyxml2::XMLNode *p_pXMLNode)
{
    DebugCube *dbc = nullptr;
    std::string name = "DynamicDebugCube" + std::to_string(s_iNodeCount);
    glm::vec3 scale = glm::vec3(1.0f);
    glm::vec3 rotation = glm::vec3(0.0f);
    glm::vec3 translation = glm::vec3(0.0f);

    std::vector<ComponentBase *> components;

    tinyxml2::XMLNode *pXMLPropCompNode = p_pXMLNode->FirstChild();
    while (pXMLPropCompNode != nullptr)
    {

        std::string tag = pXMLPropCompNode->Value();

        //-----------------------------------
        // QUERY PROPERTIES
        //-----------------------------------

        if (tag.compare("Properties") == 0)
        {
            tinyxml2::XMLNode *pXMLPropNode = pXMLPropCompNode->FirstChild();

            while (pXMLPropNode != nullptr)
            {
                std::string propTag = pXMLPropNode->Value();

                // std::cout << "DEBUGCUBE - PROPTAG:" << propTag << std::endl;

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
                        // printf("DEBUGCUBE - SCALE_RANDOM\n");
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
                            std::cerr << "DEBUGCUBE - ERROR:DATA_NOT_FOUND:SC_X" << std::endl;
                        }

                        if (propElement->QueryFloatAttribute("y", &scY) != tinyxml2::XML_SUCCESS)
                        {
                            std::cerr << "DEBUGCUBE - ERROR:DATA_NOT_FOUND:SC_Y" << std::endl;
                        }

                        if (propElement->QueryFloatAttribute("z", &scZ) != tinyxml2::XML_SUCCESS)
                        {
                            std::cerr << "DEBUGCUBE - ERROR:DATA_NOT_FOUND:SC_Z" << std::endl;
                        }

                        // std::cout << "DEBUGCUBE - SCX:" << scX << " - SCY:" << scY << " - SCZ:" << scZ << std::endl;

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
                        // printf("DEBCUBE - ROTATION_RANDOM\n");
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
                            std::cerr << "DEBUGCUBE - ERROR:DATA_NOT_FOUND:RO_X" << std::endl;
                        }

                        if (propElement->QueryFloatAttribute("y", &roY) != tinyxml2::XML_SUCCESS)
                        {
                            std::cerr << "DEBUGCUBE - ERROR:DATA_NOT_FOUND:RO_Y" << std::endl;
                        }

                        if (propElement->QueryFloatAttribute("z", &roZ) != tinyxml2::XML_SUCCESS)
                        {
                            std::cerr << "DEBUGCUBE - ERROR:DATA_NOT_FOUND:RO_Z" << std::endl;
                        }

                        // std::cout << "DEBUGCUBE - ROX:" << roX << " - ROY:" << roY << " - ROZ:" << roZ << std::endl;

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
                        // printf("DEBUGCUBE - TRANSLATION_RANDOM\n");
                        int rangeLower = -168;
                        int rangeUpper = 168;
                        translation = glm::vec3(
                            RandomNumberGenerator::getRandomNumber(rangeLower, rangeUpper),
                            RandomNumberGenerator::getRandomNumber(-128, 128),
                            RandomNumberGenerator::getRandomNumber(rangeLower, rangeUpper));
                    }
                    else
                    {
                        if (propElement->QueryFloatAttribute("x", &trX) != tinyxml2::XML_SUCCESS)
                        {
                            std::cerr << "DEBUGCUBE - ERROR:DATA_NOT_FOUND:TR_X" << std::endl;
                        }

                        if (propElement->QueryFloatAttribute("y", &trY) != tinyxml2::XML_SUCCESS)
                        {
                            std::cerr << "DEBUGCUBE - ERROR:DATA_NOT_FOUND:TR_Y" << std::endl;
                        }

                        if (propElement->QueryFloatAttribute("z", &trZ) != tinyxml2::XML_SUCCESS)
                        {
                            std::cerr << "DEBUGCUBE - ERROR:DATA_NOT_FOUND:TR_Z" << std::endl;
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
            ComponentBase *component = FactoryMethodsManager::Instance()->createComponent(dbc, pXMLPropCompNode);
            if (component != nullptr)
            {
                components.push_back(component);
            }
        }

        pXMLPropCompNode = pXMLPropCompNode->NextSibling();
    }

    dbc = new DebugCube(name, scale, rotation, translation);
    for (auto component : components)
    {
        dbc->addComponent(component);
    }

    components.clear();

    return dbc;
}

DebugCube::DebugCube(std::string p_newName, const glm::vec3 &p_vNewSc, const glm::vec3 &p_vNewRo, const glm::vec3 &p_vNewTr) : Node(p_newName, p_vNewSc, p_vNewRo, p_vNewTr)
{

    cubeCounter++;

    if (!s_pProgram)
    {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        s_pProgram = wolf::ProgramManager::CreateProgram("data/nodeWork.vsh", "data/nodeWork.fsh");
        s_pVB = wolf::BufferManager::CreateVertexBuffer(gs_cubeVertexCoords, sizeof(CubeVertex) * 36);

        s_pDecl = new wolf::VertexDeclaration();
        s_pDecl->Begin();
        s_pDecl->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
        s_pDecl->SetVertexBuffer(s_pVB);
        s_pDecl->End();
    }
}

DebugCube::~DebugCube()
{
    if (this->m_vpChildren.size() > 0)
    {

        for (auto childCube : this->m_vpChildren)
        {
            delete childCube;
            childCube = nullptr;
        }
    }
    this->m_vpChildren.clear();

    cubeCounter--;
    if (cubeCounter == 0)
    {
        delete s_pDecl;
        s_pDecl = nullptr;
        wolf::ProgramManager::DestroyProgram(s_pProgram);
        s_pProgram = nullptr;
        wolf::BufferManager::DestroyBuffer(s_pVB);
        s_pVB = nullptr;
    }
}

void DebugCube::update(float dt)
{

    Node::update(dt);
}

void DebugCube::render(const glm::mat4 &p_mProj, const glm::mat4 &p_mView)
{
    glm::mat4 mWorld = this->getTransformation();
    s_pProgram->SetUniform("projection_view", p_mProj * p_mView);
    s_pProgram->SetUniform("world", mWorld);
    s_pProgram->Bind();
    s_pDecl->Bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);

    if (this->m_vpChildren.size() > 0)
    {
        for (auto childCube : this->m_vpChildren)
        {
            childCube->render(p_mProj, p_mView);
        }
    }
}

void DebugCube::renderWithBounds(const glm::mat4 &p_mProj, const glm::mat4 &p_mView)
{

    glm::mat4 mWorld = this->getTransformation();
    s_pProgram->SetUniform("projection_view", p_mProj * p_mView);
    s_pProgram->SetUniform("world", mWorld);
    s_pProgram->Bind();
    s_pDecl->Bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);

    ComponentBase *bscb = this->GetComponent("GOC_BoundingSphere");
    if (bscb)
    {
        BoundingSphere *bosphr = dynamic_cast<BoundingSphere *>(bscb);
        bosphr->render(p_mProj, p_mView);
    }

    if (this->m_vpChildren.size() > 0)
    {
        for (auto childCube : this->m_vpChildren)
        {
            childCube->renderWithBounds(p_mProj, p_mView);
        }
    }
}

float DebugCube::calculateCentreToFurthestPoint()
{
    glm::vec3 scale = this->getGlobalScale();
    float dist = sqrt(pow(scale.x * 0.5f, 2) + pow(scale.y * 0.5f, 2) + pow(scale.z * 0.5f, 2));
    //     std::cout << "DBGCUBE - NAME: " << this->m_sName << std::endl;
    //
    //     std::cout << "DBGCUBE - DIST: " << dist << std::endl;
    return dist;
}
