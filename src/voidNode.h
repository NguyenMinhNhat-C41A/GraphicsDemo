#pragma once
#include "node.h"

class VoidNode : public Node
{
public:
    VoidNode(std::string p_sName) : Node(p_sName){};
    ~VoidNode();

    virtual void update(float p_dt) override{};
    virtual void render(const glm::mat4 &p_mProj, const glm::mat4 &p_mView) override{};
    virtual void renderWithBounds(const glm::mat4 &p_mProj, const glm::mat4 &p_mView) override{};

    virtual void initComponents() override{};

    virtual std::string getName() override { return this->m_sName; };

    virtual void setScale(const glm::vec3 &p_vNewSc) override{};
    virtual void setRotate(const glm::vec3 &p_vNewRo) override{};
    virtual void setTranslate(const glm::vec3 &p_vNewTr) override{};
    virtual glm::mat4 getTransformation() override { return glm::mat4(0.0f); };

    virtual glm::vec3 getScale() override { return glm::vec3(0.0f); };
    virtual glm::vec3 getRotate() override { return glm::vec3(0.0f); };
    virtual glm::vec3 getTranslate() override { return glm::vec3(0.0f); };

    virtual glm::vec3 getGlobalScale() override { return glm::vec3(0.0f); };
    virtual glm::vec3 getGlobalRotate() override { return glm::vec3(0.0f); };
    virtual glm::vec3 getGlobalTranslate() override { return glm::vec3(0.0f); };

    virtual bool isTransformDirty() override { return false; };

    virtual Node *getParent() override { return nullptr; };

    virtual void addChild(Node *p_pNode) override{};
    virtual std::vector<Node *> getImmediateChildren() override { return std::vector<Node *>(); };

    virtual void addComponent(ComponentBase *p_pCompBase) override{};
    virtual ComponentBase *GetComponent(std::string p_pCompID) override { return nullptr; };

    virtual float calculateCentreToFurthestPoint() override { return 0.0f; };
    virtual glm::vec3 getNodeHierarchyCentre() override { return glm::vec3(0.0f); };
};