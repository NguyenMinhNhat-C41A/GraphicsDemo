#include "dynamicQuadtree.h"

DynamicQuadtree::DynamicQuadtree(float p_fWidth, float p_fHeight, float p_fLength)
{
    VoidNode *dynamicQuadtreeBBVN = new VoidNode("DYNAMICQUADTREEBBVN - " + std::to_string((this->m_iDepthLayer - 1) * 4));
    this->m_pBoundingBox = dynamic_cast<BoundingBox *>(BoundingBox::createComponent(dynamicQuadtreeBBVN));

    this->m_pBoundingBox->setWidth(p_fWidth);
    this->m_pBoundingBox->setHeight(p_fHeight);
    this->m_pBoundingBox->setLength(p_fLength);
    this->m_pBoundingBox->setDynamicUpdate(false);
}

DynamicQuadtree::~DynamicQuadtree()
{
    if (this->isSplit)
    {
        for (auto childDQT : this->m_apChildQuadtrees)
        {
            delete childDQT;
            childDQT = nullptr;
        }
    }

    delete this->m_pBoundingBox;
    this->m_pBoundingBox = nullptr;
}

void DynamicQuadtree::update(float p_dt)
{
    if (this->isSplit)
    {
        for (auto childDQT : this->m_apChildQuadtrees)
        {
            childDQT->update(p_dt);
        }
    }
}

//--------------------------------------------------------------------------------
//
// PRIVATE METHODS
//
//--------------------------------------------------------------------------------

DynamicQuadtree::DynamicQuadtree(float p_fWidth, float p_fHeight, float p_fLength, glm::vec3 &p_vCentre, int p_iDepthLayer, int p_iQuadrant)
{
    this->m_iDepthLayer = p_iDepthLayer;
    this->m_iQuadrant = p_iQuadrant;

    VoidNode *dynamicQuadtreeBBVN = new VoidNode("QUADTREEBBVN - " + std::to_string((p_iDepthLayer - 1) * 4 + p_iQuadrant));
    this->m_pBoundingBox = dynamic_cast<BoundingBox *>(BoundingBox::createComponent(dynamicQuadtreeBBVN));

    this->m_pBoundingBox->setTranslate(p_vCentre);
    this->m_pBoundingBox->setWidth(p_fWidth);
    this->m_pBoundingBox->setHeight(p_fHeight);
    this->m_pBoundingBox->setLength(p_fLength);
    this->m_pBoundingBox->setDynamicUpdate(false);
}