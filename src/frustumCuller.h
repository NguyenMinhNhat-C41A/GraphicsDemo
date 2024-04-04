#pragma once
#include "../samplefw/FirstPersonCamera.h"
#include "../samplefw/quadtree.h"
#include "boundingSphere.h"
#include "boundingVolume.h"

class FirstPersonCamera;
class Quadtree;

class FrustumCuller
{
public:
    static std::vector<Node *> getInViewNodes(FirstPersonCamera::Frustum p_CameraFrustum, Quadtree *p_pQuadtree);
    static std::vector<Node *> getNodesFromInViewQuadtree(FirstPersonCamera::Frustum p_CameraFrustum, Quadtree *p_pQuadtree);

private:
    static bool isQuadtreeNodeInView(FirstPersonCamera::Frustum p_CameraFrustum, Quadtree *p_pQuadtree);
    static bool isNodeInView(FirstPersonCamera::Frustum p_CameraFrustum, Node *p_pNode);
    static float getSignedDistanceToPlane(Plane plane, const glm::vec3 &point);
};
