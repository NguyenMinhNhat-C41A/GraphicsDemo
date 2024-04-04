#pragma once
#include "../src/vertex.h"
#include "boundingVolume.h"
#include "boundingSphere.h"
#include "boundingVolumeIntersectCalculator.h"
class BoundingVolumeIntersectCalculator;
class BoundingBox : public BoundingVolume
{
public:
    friend BoundingVolumeIntersectCalculator;

    static ComponentBase *createComponent(Node *p_pCompNode);
    ~BoundingBox();

    std::string ComponentID() override { return "GOC_BoundingBox"; };

    virtual void init() override;
    virtual void update(float dt) override;
    virtual void render(const glm::mat4 &p_mProj, const glm::mat4 &p_mView) override;

    //-----------------------------
    // TODO: Define calculateBounds()
    //-----------------------------
    virtual void calculateBounds() override;

    virtual bool intersects(BoundingVolume *p_pBV) override;
    virtual bool intersectsPoint(const glm::vec3 &p_Point) override;
    virtual bool isIntersectingOrBeforePlane(const Plane &p_Plane) override;
    void setWidth(float p_fWidth);
    float getWidth();

    void setHeight(float p_fHeight);
    float getHeight();

    void setLength(float p_fLength);
    float getLength();

    glm::vec3 getMinMaxCoords(int p_iX, int p_iY, int p_iZ);

private:
    BoundingBox(Node *p_pCompNode);
};