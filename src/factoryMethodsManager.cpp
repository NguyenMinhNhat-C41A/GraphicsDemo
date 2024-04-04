#include "factoryMethodsManager.h"

FactoryMethodsManager *FactoryMethodsManager::s_pFactoryMethodsManager = nullptr;

//--------------------------------------------------------------------------------
//
// PUBLIC METHODS
//
//--------------------------------------------------------------------------------

void FactoryMethodsManager::CreateInstance()
{
    assert(s_pFactoryMethodsManager == nullptr);
    s_pFactoryMethodsManager = new FactoryMethodsManager();
}

void FactoryMethodsManager::DestroyInstance()
{
    assert(s_pFactoryMethodsManager != nullptr);
    delete s_pFactoryMethodsManager;
    s_pFactoryMethodsManager = nullptr;
}

FactoryMethodsManager *FactoryMethodsManager::Instance()
{
    return s_pFactoryMethodsManager;
}

//-----------------------------------
// REGISTER
//-----------------------------------

void FactoryMethodsManager::registerNodeFactoryMethod(const std::string &p_sNodeType, FactoryMethodsManager::FactoryMethodNode p_FacMedNode)
{
    FactoryMethodsManager::MapFactoryMethodNode::iterator itr = this->m_MapFactoryMethodNode.find(p_sNodeType);
    if (itr != this->m_MapFactoryMethodNode.end())
    {
        // ALREADY REGISTERED
        std::cout << "FACMEDMNGR - FACMEDNODE_ALREADY_REGISTERED:" << p_sNodeType << std::endl;
        return;
    }
    this->m_MapFactoryMethodNode.insert(std::pair<std::string, FactoryMethodNode>(p_sNodeType, p_FacMedNode));
}

void FactoryMethodsManager::registerComponentFactoryMethod(const std::string &p_sComponentType, FactoryMethodsManager::FactoryMethodComponent p_FacMedComponent)
{
    FactoryMethodsManager::MapFactoryMethodComponent::iterator itr = this->m_MapFactoryMethodComponent.find(p_sComponentType);
    if (itr != this->m_MapFactoryMethodComponent.end())
    {
        std::cout << "FACMEDMNGR - FACMEDCOMP_ALREADY_REGISTERED:" << p_sComponentType << std::endl;
        return;
    }
    this->m_MapFactoryMethodComponent.insert(std::pair<std::string, FactoryMethodComponent>(p_sComponentType, p_FacMedComponent));
}

//-----------------------------------
// CREATE
//-----------------------------------

Node *FactoryMethodsManager::createNode(const std::string &p_sDataFilePath)
{
    std::string truePath = "xmlDataFiles/" + p_sDataFilePath;
    tinyxml2::XMLDocument xmlDoc;
    tinyxml2::XMLError result = xmlDoc.LoadFile(truePath.c_str());

    //-----------------------------------
    // FILE FOUND
    //-----------------------------------

    if (result == tinyxml2::XML_SUCCESS)
    {
        tinyxml2::XMLNode *xmlNode = xmlDoc.FirstChild();

        if (xmlNode != nullptr)
        {
            std::string typeNode = xmlNode->Value();
            // std::cout << "FACMEDNODE - TYPENODE:" << typeNode << std::endl;

            FactoryMethodsManager::MapFactoryMethodNode::iterator itr = this->m_MapFactoryMethodNode.find(typeNode);

            //-----------------------------------
            // FACMEDNODE FOUND
            //-----------------------------------

            if (itr != this->m_MapFactoryMethodNode.end())
            {

                Node *node = itr->second(xmlNode);
                return node;
            }
            else
            {
                std::cerr << "FACMEDMNGR - ERROR:FACMEDNODE_NOT_FOUND:" << typeNode << std::endl;
                return nullptr;
            }
        }
        else
        {
            std::cerr << "FACMEDMNGR - ERROR:NULL" << std::endl;
            return nullptr;
        }
    }
    //-----------------------------------
    // ERRORS
    //-----------------------------------

    else if (result == tinyxml2::XML_ERROR_FILE_NOT_FOUND)
    {
        std::cout << "DYDEBCUBE - ERROR:XML_FILE_NOT_FOUND" << std::endl;
        return nullptr;
    }

    else
    {
        std::cout << "DYDEBCUBE - ERROR:" << result << std::endl;
    }
}

ComponentBase *FactoryMethodsManager::createComponent(Node *p_pCompNode, tinyxml2::XMLNode *p_pXMLNode)
{
    std::string typeComponent = p_pXMLNode->Value();
    FactoryMethodsManager::MapFactoryMethodComponent::iterator itr = this->m_MapFactoryMethodComponent.find(typeComponent);
    if (itr != this->m_MapFactoryMethodComponent.end())
    {
        ComponentBase *component = itr->second(p_pCompNode, p_pXMLNode);
        return component;
    }

    std::cerr << "FACMENDMNGR - ERROR:FACMEDCOMP_NOT_FOUND:" << typeComponent << std::endl;
    return nullptr;
}

//--------------------------------------------------------------------------------
//
// PRIVATE METHODS
//
//--------------------------------------------------------------------------------

FactoryMethodsManager::FactoryMethodsManager()
{
}
FactoryMethodsManager::~FactoryMethodsManager()
{
}