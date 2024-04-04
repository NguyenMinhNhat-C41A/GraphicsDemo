#pragma once
#include "boundingBox.h"
#include "boundingVolume.h"
#include <iostream>
class BoundingBox;
class BoundingSphere;
class BoundingVolumeIntersectCalculator
{
public:
    static bool isIntersectingBoxSphere(BoundingBox *p_pBBox, BoundingSphere *p_pBSphere);

private:
    static float clamp(float p_fVal, float p_fHi, float p_fLo);
};