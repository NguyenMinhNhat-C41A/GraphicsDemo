#pragma once
#include "../thirdparty/tinyxml2/tinyxml2.h"
#include "../src/vertex.h"
#include "boundingVolume.h"
#include "boundingVolumeIntersectCalculator.h"
#include <iostream>

class BoundingVolumeIntersectCalculator;

class BoundingSphere : public BoundingVolume
{
    friend BoundingVolumeIntersectCalculator;

public:
    static ComponentBase *createComponent(Node *p_pCompNode);
    static ComponentBase *Factory(Node *p_pCompNode, tinyxml2::XMLNode *p_pXMLNode);
    ~BoundingSphere();

    virtual std::string ComponentID() override { return "GOC_BoundingSphere"; };
    virtual void init() override;
    virtual void update(float dt) override;

    virtual void render(const glm::mat4 &p_mProj, const glm::mat4 &p_mView) override;

    virtual void calculateBounds() override;
    virtual bool intersects(BoundingVolume *p_pBV) override;
    virtual bool intersectsPoint(const glm::vec3 &p_Point) override;
    //-----------------------------
    // TODO: Define intersectsPlane()
    //-----------------------------
    virtual bool isIntersectingOrBeforePlane(const Plane &p_Plane) override;

    void setRadius(float rad);
    float getRadius();

    void setComponentNode(Node *p_pCompNode);

private:
    BoundingSphere(Node *p_pCompNode);

    float m_fRadius = 0.0f;
};