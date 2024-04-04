#include "quadtree.h"
//--------------------------------------------------------------------------------
//
// PUBLIC METHODS
//
//--------------------------------------------------------------------------------
Quadtree::Quadtree(float p_fWidth, float p_fHeight, float p_fLength)
{
    VoidNode *quadtreeBBVN = new VoidNode("QUADTREEBBVN - " + std::to_string((this->m_iDepthLayer - 1) * 4));
    this->m_pBoundingBox = dynamic_cast<BoundingBox *>(BoundingBox::createComponent(quadtreeBBVN));

    this->m_pBoundingBox->setWidth(p_fWidth);
    this->m_pBoundingBox->setHeight(p_fHeight);
    this->m_pBoundingBox->setLength(p_fLength);
    this->m_pBoundingBox->setDynamicUpdate(false);
}

Quadtree::~Quadtree()
{
    if (this->isSplit)
    {
        delete this->m_pQuadtreeQ01;
        this->m_pQuadtreeQ01 = nullptr;

        delete this->m_pQuadtreeQ02;
        this->m_pQuadtreeQ02 = nullptr;

        delete this->m_pQuadtreeQ03;
        this->m_pQuadtreeQ03 = nullptr;

        delete this->m_pQuadtreeQ04;
        this->m_pQuadtreeQ04 = nullptr;
    }

    delete this->m_pBoundingBox;
    this->m_pBoundingBox = nullptr;
    this->m_vpValidNodes.clear();
}

void Quadtree::initQuadtree()
{
    // std::cout << "QUADTREE - INIT " << std::endl;

    this->m_vpValidNodes.clear();

    for (auto node : Scene::Instance()->getNodes())
    {
        this->addNode(node);
    }
    // std::cout << "QUADTREE - INITDONE " << std::endl;
}

void Quadtree::renderBounds(const glm::mat4 &p_mProj, const glm::mat4 &p_mView)
{
    glm::vec3 boxCentre = this->m_pBoundingBox->getGlobalCentre();
    this->m_pBoundingBox->render(p_mProj, p_mView);
    if (this->isSplit)
    {
        this->m_pQuadtreeQ01->renderBounds(p_mProj, p_mView);
        this->m_pQuadtreeQ02->renderBounds(p_mProj, p_mView);
        this->m_pQuadtreeQ03->renderBounds(p_mProj, p_mView);
        this->m_pQuadtreeQ04->renderBounds(p_mProj, p_mView);
    }
}

std::vector<Node *> Quadtree::getValidNodes()
{
    std::vector<Node *> validNodes;
    if (this->isSplit)
    {
        std::vector<Node *> validNodesQ01 = this->m_pQuadtreeQ01->getValidNodes();

        std::vector<Node *> validNodesQ02 = this->m_pQuadtreeQ02->getValidNodes();

        std::vector<Node *> validNodesQ03 = this->m_pQuadtreeQ03->getValidNodes();

        std::vector<Node *> validNodesQ04 = this->m_pQuadtreeQ04->getValidNodes();

        if (validNodesQ01.size() > 0)
        {

            for (auto node : validNodesQ01)
            {
                bool isNodeNotIn = true;

                for (auto existingNode : validNodes)
                {
                    if (node->getName() == existingNode->getName())
                    {
                        isNodeNotIn = false;
                        break;
                    }
                }

                if (isNodeNotIn)
                {
                    validNodes.push_back(node);
                }
            }
        }

        if (validNodesQ02.size() > 0)
        {
            for (auto node : validNodesQ02)
            {
                bool isNodeNotIn = true;

                for (auto existingNode : validNodes)
                {
                    if (node->getName() == existingNode->getName())
                    {
                        isNodeNotIn = false;
                        break;
                    }
                }

                if (isNodeNotIn)
                {
                    validNodes.push_back(node);
                }
            }
        }

        if (validNodesQ03.size() > 0)
        {
            for (auto node : validNodesQ03)
            {
                bool isNodeNotIn = true;

                for (auto existingNode : validNodes)
                {
                    if (node->getName() == existingNode->getName())
                    {
                        isNodeNotIn = false;
                        break;
                    }
                }

                if (isNodeNotIn)
                {
                    validNodes.push_back(node);
                }
            }
        }

        if (validNodesQ04.size() > 0)
        {
            for (auto node : validNodesQ04)
            {
                bool isNodeNotIn = true;

                for (auto existingNode : validNodes)
                {
                    if (node->getName() == existingNode->getName())
                    {
                        isNodeNotIn = false;
                        break;
                    }
                }

                if (isNodeNotIn)
                {
                    validNodes.push_back(node);
                }
            }
        }
    }
    else
    {
        validNodes = this->m_vpValidNodes;
    }
    return validNodes;
}

BoundingBox *Quadtree::getBoundingBox()
{
    return this->m_pBoundingBox;
}

Quadtree *Quadtree ::getQuadtreeQ01()
{
    return this->m_pQuadtreeQ01;
}

Quadtree *Quadtree ::getQuadtreeQ02()
{

    return this->m_pQuadtreeQ02;
}
Quadtree *Quadtree ::getQuadtreeQ03()
{

    return this->m_pQuadtreeQ03;
}

Quadtree *Quadtree ::getQuadtreeQ04()
{
    return this->m_pQuadtreeQ04;
}

//--------------------------------------------------------------------------------
//
// PRIVATE METHODS
//
//--------------------------------------------------------------------------------

Quadtree::Quadtree(float p_fWidth, float p_fHeight, float p_fLength, glm::vec3 &p_vCentre, int p_iDepthLayer, int p_iQuadrant)
{

    this->m_iDepthLayer = p_iDepthLayer;

    VoidNode *quadtreeBBVN = new VoidNode("QUADTREEBBVN - " + std::to_string((p_iDepthLayer - 1) * 4 + p_iQuadrant));

    this->m_pBoundingBox = dynamic_cast<BoundingBox *>(BoundingBox::createComponent(quadtreeBBVN));
    this->m_pBoundingBox->setTranslate(p_vCentre);
    this->m_pBoundingBox->setWidth(p_fWidth);
    this->m_pBoundingBox->setHeight(p_fHeight);
    this->m_pBoundingBox->setLength(p_fLength);
    this->m_pBoundingBox->setDynamicUpdate(false);

    this->m_iQuadrant = p_iQuadrant;
}

bool Quadtree::isQuadtreeSplit()
{
    return this->isSplit;
}

bool Quadtree::isNodeWithinWorldBounds(Node *p_pNode)
{
    //--------------------------------------------------------------------------------
    //
    // TODO: Generify method to support more than BoundingSphere
    //
    //--------------------------------------------------------------------------------

    ComponentBase *compBase = p_pNode->GetComponent("GOC_BoundingSphere");
    if (compBase)
    {
        // std::cout << "QUADTREE - BOSPHR_TRUE" << std::endl;
        BoundingSphere *boSphr = dynamic_cast<BoundingSphere *>(compBase);
        return this->m_pBoundingBox->intersects(boSphr);
    }
    else
    {

        // std::cout << "QUADTREE - BV_FALSE" << std::endl;
        glm::vec3 nodePos = p_pNode->getGlobalTranslate();
        bool res = this->m_pBoundingBox->intersectsPoint(nodePos);
        return res;
    }
}

void Quadtree::addNode(Node *p_pNode)
{
    // std::cout << "QUADTREE - DEPTH: " << this->m_iDepthLayer << std::endl;
    // std::cout << "QUADTREE - QUADRANT: " << this->m_iQuadrant << std::endl;
    // std::cout << "QUADTREE - NODE_NAME: " << p_pNode->getName() << std::endl;
    if (this->isNodeWithinWorldBounds(p_pNode))
    {
        if (!this->isSplit)
        {
            this->m_vpValidNodes.push_back(p_pNode);
            if (this->m_vpValidNodes.size() >= NODES_CAP && this->m_iDepthLayer < DEPTH_CAP)
            {
                // std::cout << "QUADTREE ----------------------------------------- SPLIT" << std::endl;
                this->isSplit = true;

                glm::vec3 currentCentre = this->m_pBoundingBox->getGlobalCentre();

                this->m_pQuadtreeQ01 = new Quadtree(this->m_pBoundingBox->getWidth() * 0.5f, this->m_pBoundingBox->getHeight(), this->m_pBoundingBox->getLength() * 0.5f,
                                                    glm::vec3(currentCentre.x + (this->m_pBoundingBox->getWidth() * 0.25f),
                                                              currentCentre.y,
                                                              currentCentre.z + (this->m_pBoundingBox->getLength()) * 0.25f),
                                                    this->m_iDepthLayer + 1, 1);

                this->m_pQuadtreeQ02 = new Quadtree(this->m_pBoundingBox->getWidth() * 0.5f, this->m_pBoundingBox->getHeight(), this->m_pBoundingBox->getLength() * 0.5f,
                                                    glm::vec3(currentCentre.x - (this->m_pBoundingBox->getWidth() * 0.25f),
                                                              currentCentre.y,
                                                              currentCentre.z + (this->m_pBoundingBox->getLength()) * 0.25f),
                                                    this->m_iDepthLayer + 1, 2);

                this->m_pQuadtreeQ03 = new Quadtree(this->m_pBoundingBox->getWidth() * 0.5f, this->m_pBoundingBox->getHeight(), this->m_pBoundingBox->getLength() * 0.5f,
                                                    glm::vec3(currentCentre.x - (this->m_pBoundingBox->getWidth() * 0.25f),
                                                              currentCentre.y,
                                                              currentCentre.z - (this->m_pBoundingBox->getLength()) * 0.25f),
                                                    this->m_iDepthLayer + 1, 3);

                this->m_pQuadtreeQ04 = new Quadtree(this->m_pBoundingBox->getWidth() * 0.5f, this->m_pBoundingBox->getHeight(), this->m_pBoundingBox->getLength() * 0.5f,
                                                    glm::vec3(currentCentre.x + (this->m_pBoundingBox->getWidth() * 0.25f),
                                                              currentCentre.y,
                                                              currentCentre.z - (this->m_pBoundingBox->getLength()) * 0.25f),
                                                    this->m_iDepthLayer + 1, 4);

                for (auto node : this->m_vpValidNodes)
                {
                    this->m_pQuadtreeQ01->addNode(node);

                    this->m_pQuadtreeQ02->addNode(node);

                    this->m_pQuadtreeQ03->addNode(node);

                    this->m_pQuadtreeQ04->addNode(node);
                }
                this->m_vpValidNodes.clear();
            }
        }
        else
        {
            this->m_pQuadtreeQ01->addNode(p_pNode);

            this->m_pQuadtreeQ02->addNode(p_pNode);

            this->m_pQuadtreeQ03->addNode(p_pNode);

            this->m_pQuadtreeQ04->addNode(p_pNode);
        }
    }
    else
    {

        // std::cout << "QUADTREE - NODE_INVALID" << std::endl;
    }
}