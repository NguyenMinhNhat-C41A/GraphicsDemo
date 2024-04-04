#pragma once
#include "componentBase.h"
#include "transform.h"
#include "../wolf/wolf.h"
#include "../samplefw/plane.h"
class BoundingVolume : public ComponentBase
{

public:
    virtual void init() override{};
    virtual void update(float dt) override{};
    virtual void render(const glm::mat4 &p_mProj, const glm::mat4 &p_mView) = 0;
    void setRender(bool renderBool) { this->m_bIsRenderOn = renderBool; }

    void setDynamicUpdate(bool dyUpBool) { this->m_bIsDynamicUpdate = dyUpBool; };

    virtual void calculateBounds() = 0;
    virtual bool intersects(BoundingVolume *p_pBV) = 0;
    virtual bool intersectsPoint(const glm::vec3 &p_Point) = 0;
    virtual bool isIntersectingOrBeforePlane(const Plane &p_Plane) = 0;

    virtual glm::vec3 getGlobalCentre()
    {
        glm::vec3 globalCentre = this->m_pTransform->getTranslate() + this->m_pCompNode->getNodeHierarchyCentre();
        return globalCentre;
    }

    virtual glm::mat4 getGlobalTransformation()
    {
        glm::mat4 transformation = this->m_pCompNode->getTransformation() * this->m_pTransform->getTransformation();
        return transformation;
    }

    void setScale(const glm::vec3 &m_vSc) { this->m_pTransform->setScale(m_vSc); };
    void setRotate(const glm::vec3 &m_vRo) { this->m_pTransform->setRotate(m_vRo); };
    void setTranslate(const glm::vec3 &m_vTr) { this->m_pTransform->setTranslate(m_vTr); };

protected:
    BoundingVolume(Node *p_pCompNode) : ComponentBase(p_pCompNode) { this->m_pTransform = new Transform(); };
    virtual ~BoundingVolume()
    {
        delete this->m_pTransform;
        this->m_pTransform = nullptr;
    };

    Transform *m_pTransform = nullptr;

    wolf::VertexBuffer *m_pVB = nullptr;
    wolf::VertexDeclaration *m_pDecl = nullptr;
    wolf::Program *m_pProgram = nullptr;

    std::vector<glm::vec3> m_vBoundingVolumeVertices;

    bool m_bIsRenderOn = false;
    bool m_bIsDynamicUpdate = true;

    bool m_bIsDynamicInit = true;

    bool m_bBoundsDirty = false;

    glm::vec4 m_vBoundsColour = glm::vec4(1.0f);
};