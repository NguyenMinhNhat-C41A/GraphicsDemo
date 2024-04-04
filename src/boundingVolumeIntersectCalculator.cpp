#include "boundingVolumeIntersectCalculator.h"

bool BoundingVolumeIntersectCalculator::isIntersectingBoxSphere(BoundingBox *p_pBBox, BoundingSphere *p_pBSphere)
{
    glm::vec3 boxCentre = p_pBBox->getGlobalCentre();
    glm::vec3 sphereCentre = p_pBSphere->getGlobalCentre();
    // std::cout << "BVIS - BBOX_CENTRE_POS: " << boxCentre.x << ", " << boxCentre.y << ", " << boxCentre.z << std::endl;
    // std::cout << "BVIS - BSPHR_CENTRE_POS: " << sphereCentre.x << ", " << sphereCentre.y << ", " << sphereCentre.z << std::endl;

    glm::vec3 boxMaxCoords = p_pBBox->getMinMaxCoords(1, 1, 1);
    glm::vec3 boxMinCoords = p_pBBox->getMinMaxCoords(0, 0, 0);

    // std::cout << "BVIS - BBOX_MAX_POS: " << boxMaxCoords.x << ", " << boxMaxCoords.y << ", " << boxMaxCoords.z << std::endl;
    // std::cout << "BVIS - BBOX_MIN_POS: " << boxMinCoords.x << ", " << boxMinCoords.y << ", " << boxMinCoords.z << std::endl;

    float xMax = boxMaxCoords.x;
    float xMin = boxMinCoords.x;

    float yMax = boxMaxCoords.y;
    float yMin = boxMinCoords.y;

    float zMax = boxMaxCoords.z;
    float zMin = boxMinCoords.z;

    glm::vec3 closestPointToBox = glm::vec3(
        BoundingVolumeIntersectCalculator::clamp(sphereCentre.x, xMax, xMin),
        BoundingVolumeIntersectCalculator::clamp(sphereCentre.y, yMax, yMin),
        BoundingVolumeIntersectCalculator::clamp(sphereCentre.z, zMax, zMin));

    float distSquared = pow((closestPointToBox.x - sphereCentre.x), 2) + pow((closestPointToBox.y - sphereCentre.y), 2) + pow((closestPointToBox.z - sphereCentre.z), 2);
    float radiusSquared = pow(p_pBSphere->m_fRadius, 2);
    //     std::cout << "BVIS - SPHR_RAD: " << p_pBSphere->m_fRadius << std::endl;
    // std::cout << "BVIS - CLOSEST_POS: " << closestPointToBox.x << ", " << closestPointToBox.y << ", " << closestPointToBox.z << std::endl;
    // std::cout << "BVIS - DIST_SQR: " << distSquared << std::endl;
    if (distSquared <= radiusSquared)
    {
        // std::cout << "BVIS - BV_INTERSECT TRUE" << std::endl;
        return true;
    }
    // std::cout << "BVIS - BV_INTERSECT FALSE" << std::endl;
    return false;
}

float BoundingVolumeIntersectCalculator::clamp(float p_fVal, float p_fHi, float p_fLo)
{
    if (p_fVal < p_fLo)
    {
        p_fVal = p_fLo;
    }
    else if (p_fVal > p_fHi)
    {
        p_fVal = p_fHi;
    }

    return p_fVal;
}