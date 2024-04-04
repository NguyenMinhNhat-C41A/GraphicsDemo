#include "Node.h"

int Node::s_iNodeCount = 0;

Node::Node(std::string p_sNewName)
{

    s_iNodeCount++;
    this->m_sName = p_sNewName;
    this->m_pTransform = new Transform();
}
Node::Node(std::string p_sNewName, const glm::vec3 &p_vNewSc, const glm::vec3 &p_vNewRo, const glm::vec3 &p_vNewTr)
{
    s_iNodeCount++;
    this->m_sName = p_sNewName;
    this->m_pTransform = new Transform();
    this->m_pTransform->setScale(p_vNewSc);
    this->m_pTransform->setRotate(p_vNewRo);
    this->m_pTransform->setTranslate(p_vNewTr);
}

Node::~Node()
{
    delete this->m_pTransform;
    this->m_pTransform = nullptr;
}

void Node::initComponents()
{
    if (this->m_vpChildren.size() > 0)
    {

        for (auto childNode : this->m_vpChildren)
        {
            childNode->initComponents();
        }
    }

    for (CompMap::iterator itr = this->m_ComponentMap.begin(); itr != this->m_ComponentMap.end(); ++itr)
    {

        // std::cout << "NODE - COMPMAP_SIZE: " << this->m_ComponentMap.size() << std::endl;
        ComponentBase *component = itr->second;
        // std::cout << "NODE - COMP_NAME: " << component->ComponentID() << std::endl;

        // std::cout << "NODE - NODE_NAME: " << this->m_sName << std::endl;
        // std::cout << "NODE - NODE_GLOBAL_POS: " << this->getGlobalTranslate().x << ", " << this->getGlobalTranslate().y << ", " << this->getGlobalTranslate().z << std::endl;
        component->init();
    }
}
void Node::update(float p_dt)
{

    if (this->m_vpChildren.size() > 0)
    {

        for (auto childCube : this->m_vpChildren)
        {
            childCube->update(p_dt);
        }
    }
    for (CompMap::iterator itr = this->m_ComponentMap.begin(); itr != this->m_ComponentMap.end(); ++itr)
    {
        // std::cout << "NODE - COMPMAP_SIZE: " << this->m_ComponentMap.size() << std::endl;
        ComponentBase *component = itr->second;
        // std::cout << "NODE - COMP_NAME: " << component->ComponentID() << std::endl;
        component->update(p_dt);
    }
}

std::string Node::getName()
{
    return this->m_sName;
}

void Node::setScale(const glm::vec3 &p_vNewSc)
{
    this->m_pTransform->setScale(p_vNewSc);

    for (CompMap::iterator itr = this->m_ComponentMap.begin(); itr != this->m_ComponentMap.end(); ++itr)
    {
        ComponentBase *component = itr->second;
        component->nodeTransformDirty();
    }
}

void Node::setRotate(const glm::vec3 &p_vNewRo)
{
    this->m_pTransform->setRotate(p_vNewRo);

    for (CompMap::iterator itr = this->m_ComponentMap.begin(); itr != this->m_ComponentMap.end(); ++itr)
    {
        ComponentBase *component = itr->second;
        component->nodeTransformDirty();
    }
}

void Node::setTranslate(const glm::vec3 &p_vNewTr)
{
    this->m_pTransform->setTranslate(p_vNewTr);

    for (CompMap::iterator itr = this->m_ComponentMap.begin(); itr != this->m_ComponentMap.end(); ++itr)
    {
        ComponentBase *component = itr->second;
        component->nodeTransformDirty();
    }
}

glm::mat4 Node::getTransformation()
{
    glm::mat4 transformMatrix = this->m_pTransform->getTransformation();
    if (this->m_pParent)
    {
        return this->m_pParent->getTransformation() * transformMatrix;
    }
    return transformMatrix;
}

glm::vec3 Node::getScale()
{
    return this->m_pTransform->getScale();
}

glm::vec3 Node::getRotate()
{

    return this->m_pTransform->getRotate();
}

glm::vec3 Node::getTranslate()
{

    return this->m_pTransform->getTranslate();
}

glm::vec3 Node::getGlobalScale()
{
    // glm::vec3 scale = this->getScale();
    // if (this->m_pParent)
    // {
    //     scale = this->m_pParent->getGlobalScale() * scale;
    // }
    // return scale;

    glm::mat4 transform = this->getTransformation();
    float scaleX = glm::length(glm::vec3(transform[0][0], transform[1][0], transform[2][0]));
    float scaleY = glm::length(glm::vec3(transform[0][1], transform[1][1], transform[2][1]));
    float scaleZ = glm::length(glm::vec3(transform[0][2], transform[1][2], transform[2][2]));

    return glm::vec3(scaleX, scaleY, scaleZ);
}
glm::vec3 Node::getGlobalRotate()
{
    // glm::vec3 rotate = this->getRotate();
    // if (this->m_pParent)
    // {
    //     rotate = this->m_pParent->getGlobalRotate() + rotate;
    // }
    // return rotate;

    glm::mat4 transform = this->getTransformation();
    float scaleX = glm::length(glm::vec3(transform[0][0], transform[1][0], transform[2][0]));
    float scaleY = glm::length(glm::vec3(transform[0][1], transform[1][1], transform[2][1]));
    float scaleZ = glm::length(glm::vec3(transform[0][2], transform[1][2], transform[2][2]));

    glm::mat4 rotationMatrix = transform;
    for (int i = 0; i < 3; ++i)
    {
        rotationMatrix[i][0] /= scaleX;
        rotationMatrix[i][1] /= scaleY;
        rotationMatrix[i][2] /= scaleZ;
    }

    glm::vec3 rotate = glm::vec3(0.0f);
    rotate.x = atan2(rotationMatrix[2][1], rotationMatrix[2][2]);
    rotate.y = atan2(-rotationMatrix[2][0], sqrt(pow(rotationMatrix[2][1], 2) + pow(rotationMatrix[2][2], 2)));
    rotate.z = atan2(rotationMatrix[1][0], rotationMatrix[0][0]);

    rotate.x = glm::degrees(rotate.x);
    rotate.y = glm::degrees(rotate.y);
    rotate.z = glm::degrees(rotate.z);

    return -rotate;
}
glm::vec3 Node::getGlobalTranslate()
{
    // glm::vec3 translate = this->getTranslate();
    // if (this->m_pParent)
    // {
    //     translate = this->m_pParent->getGlobalTranslate() + translate;
    // }
    // return translate;

    return glm::vec3(this->getTransformation()[3]);
}

bool Node::isTransformDirty()
{
    return this->m_pTransform->getDirtyBit();
}

void Node::addChild(Node *p_pNode)
{
    this->m_vpChildren.push_back(p_pNode);
    p_pNode->m_pParent = this;
    for (CompMap::iterator itr = this->m_ComponentMap.begin(); itr != this->m_ComponentMap.end(); ++itr)
    {
        ComponentBase *component = itr->second;
        component->nodeImmediateChildrenCountDirty();
    }
}

Node *Node::getParent()
{
    return this->m_pParent;
}

std::vector<Node *> Node::getImmediateChildren()
{
    return this->m_vpChildren;
}

void Node::addComponent(ComponentBase *p_pCompBase)
{
    if (this->m_ComponentMap.find(p_pCompBase->ComponentID()) == this->m_ComponentMap.end())
    {
        this->m_ComponentMap.insert(std::pair<std::string, ComponentBase *>(p_pCompBase->ComponentID(), p_pCompBase));
        p_pCompBase->setComponentNode(this);
    }
}

ComponentBase *Node::GetComponent(std::string p_pCompID)
{
    CompMap::iterator itr = this->m_ComponentMap.find(p_pCompID);
    if (itr != this->m_ComponentMap.end())
    {
        return itr->second;
    }
    return nullptr;
}

float Node::calculateCentreToFurthestPoint()
{
    return 0.0f;
}

glm::vec3 Node::getNodeHierarchyCentre()
{
    glm::vec3 res = glm::vec3(0.0f);
    res += this->getGlobalTranslate();
    if (this->getImmediateChildren().size() > 0)
    {
        for (auto childNode : this->getImmediateChildren())
        {
            res += childNode->getGlobalTranslate();
        }
    }

    res = res * static_cast<float>(1.0f / (this->getImmediateChildren().size() + 1));
    // std::cout << "NODE - HIER_CENTRE: " << res.x << ", " << res.y << ", " << res.z << std::endl;
    return res;
}