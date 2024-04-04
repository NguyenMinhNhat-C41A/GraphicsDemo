#pragma once

#include <functional>
#include <vector>
#include <map>
#include "../wolf/wolf.h"
#include "../thirdparty/tinyxml2/tinyxml2.h"
#include "node.h"
#include "componentBase.h"

class FactoryMethodsManager
{
public:
    //--------------------------------------------------------------------------------
    //
    //  TYPEDEFS
    //
    //--------------------------------------------------------------------------------

    typedef std::function<Node *(tinyxml2::XMLNode *p_XMLNode)> FactoryMethodNode;
    typedef std::map<std::string, FactoryMethodNode> MapFactoryMethodNode;

    typedef std::function<ComponentBase *(Node *p_pCompNode, tinyxml2::XMLNode *p_XMLNode)> FactoryMethodComponent;
    typedef std::map<std::string, FactoryMethodComponent> MapFactoryMethodComponent;

    //--------------------------------------------------------------------------------
    //
    //  PUBLIC METHODS
    //
    //--------------------------------------------------------------------------------

    static void CreateInstance();
    static void DestroyInstance();
    static FactoryMethodsManager *Instance();

    void registerNodeFactoryMethod(const std::string &p_sNodeType, FactoryMethodNode p_FacMedNode);

    void registerComponentFactoryMethod(const std::string &p_sComponentType, FactoryMethodComponent p_FacMedComponent);

    Node *createNode(const std::string &p_sDataFilePath);

    // CALL WITHIN CONSTRUCTOR OF NODE
    ComponentBase *createComponent(Node *p_pCompNode, tinyxml2::XMLNode *p_pXMLNode);

private:
    //--------------------------------------------------------------------------------
    //
    // PRIVATE METHODS
    //
    //--------------------------------------------------------------------------------

    FactoryMethodsManager();
    ~FactoryMethodsManager();

    //--------------------------------------------------------------------------------
    //
    // PRIVATE VARIABLES
    //
    //--------------------------------------------------------------------------------

    static FactoryMethodsManager *s_pFactoryMethodsManager;

    MapFactoryMethodNode m_MapFactoryMethodNode;
    MapFactoryMethodComponent m_MapFactoryMethodComponent;
};