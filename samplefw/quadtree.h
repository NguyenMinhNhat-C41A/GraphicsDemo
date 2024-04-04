#pragma once

#include <iostream>
#include "scene.h"
#include "../src/voidNode.h"
#include "../src/boundingBox.h"
#include "../src/boundingSphere.h"
#include "../src/frustumCuller.h"

//--------------------------------------------------------------------------------
//
//
//
//--------------------------------------------------------------------------------
class FrustumCuller;

class Quadtree
{
    friend FrustumCuller;

public:
    Quadtree(float p_fWidth, float p_fHeight, float p_fLength);
    ~Quadtree();
    void initQuadtree();

    void renderBounds(const glm::mat4 &p_mProj, const glm::mat4 &p_mView);

    std::vector<Node *> getValidNodes();

    BoundingBox *getBoundingBox();

    Quadtree *getQuadtreeQ01();
    Quadtree *getQuadtreeQ02();
    Quadtree *getQuadtreeQ03();
    Quadtree *getQuadtreeQ04();

    void setQuadrant(int q);

    int getQuadrant() { return this->m_iQuadrant; }
    int getDepthLayer() { return this->m_iDepthLayer; }

private:
    Quadtree(float p_fWidth, float p_fHeight, float p_fLength, glm::vec3 &p_vCentre, int p_iDepthLayer, int p_iQuadrant);
    bool isQuadtreeSplit();
    bool isNodeWithinWorldBounds(Node *p_pNode);
    void addNode(Node *p_pNode);

    // void passValidNodes(std::vector<Node *> p_vVNos);
    // void calculateValidNodes();

    int m_iDepthLayer = 1;
    const int NODES_CAP = 7;
    const int DEPTH_CAP = 7;

    bool isSplit = false;

    std::vector<Node *> m_vpValidNodes;

    BoundingBox *m_pBoundingBox = nullptr;

    Quadtree *m_pQuadtreeQ01 = nullptr;

    Quadtree *m_pQuadtreeQ02 = nullptr;

    Quadtree *m_pQuadtreeQ03 = nullptr;

    Quadtree *m_pQuadtreeQ04 = nullptr;

    int m_iQuadrant = 0;
};