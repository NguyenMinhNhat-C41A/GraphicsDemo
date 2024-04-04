#include "frustumCuller.h"

std::vector<Node *> FrustumCuller::getInViewNodes(FirstPersonCamera::Frustum p_CameraFrustum, Quadtree *p_pQuadtree)
{
    std::vector<Node *> inViewNodes;
    std::vector<Node *> candidateNodes = FrustumCuller::getNodesFromInViewQuadtree(p_CameraFrustum, p_pQuadtree);
    for (auto node : candidateNodes)

    {
        if (FrustumCuller::isNodeInView(p_CameraFrustum, node))
        {
            inViewNodes.push_back(node);
        }
    }

    // std::cout << "FRCL - CANDIDATE_NODES_COUNT: " << candidateNodes.size() << std::endl;
    // std::cout << "FRCL - INVIEW_NODES_COUNT: " << inViewNodes.size() << std::endl;
    return inViewNodes;

    // return FrustumCuller::getNodesFromInViewQuadtree(p_CameraFrustum, p_pQuadtree);
}
std::vector<Node *> FrustumCuller::getNodesFromInViewQuadtree(FirstPersonCamera::Frustum p_CameraFrustum, Quadtree *p_pQuadtree)
{

    // std::cout << "FRCL - UNSPLIT_QNODE_D" << p_pQuadtree->getDepthLayer() << "_Q" << p_pQuadtree->getQuadrant() << std::endl;
    if (FrustumCuller::isQuadtreeNodeInView(p_CameraFrustum, p_pQuadtree))
    {
        if (!p_pQuadtree->isQuadtreeSplit())
        {
            return p_pQuadtree->getValidNodes();
        }

        std::vector<Node *> inViewNodes;

        //-------------------------------------
        // TODO: Create better existing Node check algorithm
        //-------------------------------------

        Quadtree *quadtreeQ01 = p_pQuadtree->getQuadtreeQ01();
        std::vector<Node *> q01Nodes = FrustumCuller::getNodesFromInViewQuadtree(p_CameraFrustum, quadtreeQ01);
        if (q01Nodes.size() > 0)
        {
            for (auto node : q01Nodes)
            {
                bool isNodeNotIn = true;

                for (auto existingNode : inViewNodes)
                {
                    if (node->getName() == existingNode->getName())
                    {
                        isNodeNotIn = false;
                        break;
                    }
                }
                if (isNodeNotIn)
                {
                    inViewNodes.push_back(node);
                }
            }
        }

        Quadtree *quadtreeQ02 = p_pQuadtree->getQuadtreeQ02();
        std::vector<Node *> q02Nodes = FrustumCuller::getNodesFromInViewQuadtree(p_CameraFrustum, quadtreeQ02);
        if (q02Nodes.size() > 0)
        {
            for (auto node : q02Nodes)
            {
                bool isNodeNotIn = true;

                for (auto existingNode : inViewNodes)
                {
                    if (node->getName() == existingNode->getName())
                    {
                        isNodeNotIn = false;
                        break;
                    }
                }
                if (isNodeNotIn)
                {
                    inViewNodes.push_back(node);
                }
            }
        }

        Quadtree *quadtreeQ03 = p_pQuadtree->getQuadtreeQ03();
        std::vector<Node *> q03Nodes = FrustumCuller::getNodesFromInViewQuadtree(p_CameraFrustum, quadtreeQ03);
        if (q03Nodes.size() > 0)
        {
            for (auto node : q03Nodes)
            {
                bool isNodeNotIn = true;

                for (auto existingNode : inViewNodes)
                {
                    if (node->getName() == existingNode->getName())
                    {
                        isNodeNotIn = false;
                        break;
                    }
                }
                if (isNodeNotIn)
                {
                    inViewNodes.push_back(node);
                }
            }
        }

        Quadtree *quadtreeQ04 = p_pQuadtree->getQuadtreeQ04();
        std::vector<Node *> q04Nodes = FrustumCuller::getNodesFromInViewQuadtree(p_CameraFrustum, quadtreeQ04);
        if (q04Nodes.size() > 0)
        {
            for (auto node : q04Nodes)
            {
                bool isNodeNotIn = true;

                for (auto existingNode : inViewNodes)
                {
                    if (node->getName() == existingNode->getName())
                    {
                        isNodeNotIn = false;
                        break;
                    }
                }
                if (isNodeNotIn)
                {
                    inViewNodes.push_back(node);
                }
            }
        }

        return inViewNodes;

        // std::cout << "FRCL - SPLIT_QNODE" << std::endl;
    }
    std::vector<Node *> nullVector;
    return nullVector;
}

//--------------------------------------------------------------------------------
//
// PRIVATE METHODS
//
//--------------------------------------------------------------------------------

bool FrustumCuller::isQuadtreeNodeInView(FirstPersonCamera::Frustum p_CameraFrustum, Quadtree *p_pQuadtree)
{
    BoundingBox *quadtreeBoundingBox = p_pQuadtree->getBoundingBox();
    glm::vec3 boxCentre = quadtreeBoundingBox->getGlobalCentre();
    // std::cout << "FRCL - QNODE_BBOX_CENTRE: " << boxCentre.x << ", " << boxCentre.y << ", " << boxCentre.z << std::endl;
    bool result = quadtreeBoundingBox->isIntersectingOrBeforePlane(p_CameraFrustum.nearPlane) &&
                  quadtreeBoundingBox->isIntersectingOrBeforePlane(p_CameraFrustum.farPlane) &&
                  quadtreeBoundingBox->isIntersectingOrBeforePlane(p_CameraFrustum.rightPlane) &&
                  quadtreeBoundingBox->isIntersectingOrBeforePlane(p_CameraFrustum.leftPlane) &&
                  quadtreeBoundingBox->isIntersectingOrBeforePlane(p_CameraFrustum.topPlane) &&
                  quadtreeBoundingBox->isIntersectingOrBeforePlane(p_CameraFrustum.bottomPlane);

    // std::cout << "FRCL - QNODE_INVIEW: " << result << std::endl;
    return result;
}

//----------------------------
// TODO: Generify method to support more than BoundingSphere
//----------------------------
bool FrustumCuller::isNodeInView(FirstPersonCamera::Frustum p_CameraFrustum, Node *p_pNode)
{
    ComponentBase *bscb = p_pNode->GetComponent("GOC_BoundingSphere");
    // std::cout << "FRCL - ID: " << bscb->ComponentID() << std::endl;
    if (bscb)
    {
        BoundingSphere *boSphr = dynamic_cast<BoundingSphere *>(bscb);
        glm::vec3 centre = boSphr->getGlobalCentre();
        bool result = boSphr->isIntersectingOrBeforePlane(p_CameraFrustum.nearPlane) &&
                      boSphr->isIntersectingOrBeforePlane(p_CameraFrustum.farPlane) &&
                      boSphr->isIntersectingOrBeforePlane(p_CameraFrustum.rightPlane) &&
                      boSphr->isIntersectingOrBeforePlane(p_CameraFrustum.leftPlane) &&
                      boSphr->isIntersectingOrBeforePlane(p_CameraFrustum.topPlane) &&
                      boSphr->isIntersectingOrBeforePlane(p_CameraFrustum.bottomPlane);
        return result;
    }
    // std::cout << "FRCL - ERROR: NO_BV" << std::endl;
    return false;
}

float FrustumCuller::getSignedDistanceToPlane(Plane plane, const glm::vec3 &point)
{

    return glm::dot(plane.normal, point) + plane.distance;
}