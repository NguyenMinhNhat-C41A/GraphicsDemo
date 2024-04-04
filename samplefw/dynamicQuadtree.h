#pragma once
#include "scene.h"
#include <iostream>
#include <array>
#include "../src/boundingBox.h"
#include "../src/boundingSphere.h"

//--------------------------------------------------------------------------------
//
//
//
//--------------------------------------------------------------------------------
class DynamicQuadtree
{
public:
    DynamicQuadtree(float p_fWidth, float p_fHeight, float p_fLength);
    ~DynamicQuadtree();

    void update(float p_dt);
    void renderBounds(const glm::mat4 &p_mProj, const glm::mat4 &p_mView);

    std::vector<Node *> getValidNodes();

    BoundingBox *getBoundingBox();

    std::array<DynamicQuadtree *, 4> getChildDynamicQuadtrees();
    bool isDynamicQuadtreeSplit();
    void setQuadrant(int q);

    int getQuadrant() { return this->m_iQuadrant; }
    int getDepthLayer() { return this->m_iDepthLayer; }

private:
    DynamicQuadtree(float p_fWidth, float p_fHeight, float p_fLength, glm::vec3 &p_vCentre, int p_iDepthLayer, int p_iQuadrant);

    std::vector<Node *> getValidNodes(std::vector<Node *>);

    bool isNodeWithinWorldBounds(Node *p_pNode);
    void addNode(Node *p_pNode);

    // void passValidNodes(std::vector<Node *> p_vVNos);
    // void calculateValidNodes();

    int m_iDepthLayer = 1;
    int m_iQuadrant = 0;

    const int NODES_CAP = 7;
    const int DEPTH_CAP = 7;

    bool isSplit = false;
    bool areChildrenInitialised = false;

    BoundingBox *m_pBoundingBox = nullptr;

    std::array<DynamicQuadtree *, 4> m_apChildQuadtrees;
};