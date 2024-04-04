#pragma once
#include <vector>
#include <map>
#include "../wolf/wolf.h"
#include "rng.h"
#include "componentBase.h"
#include "transform.h"

class ComponentBase;
class Node
{

    typedef std::map<std::string, ComponentBase *> CompMap;

public:
    friend ComponentBase;

    Node(std::string p_sNewName);
    Node(std::string p_sNewName, const glm::vec3 &p_vNewSc, const glm::vec3 &p_vNewRo, const glm::vec3 &p_vNewTr);
    ~Node();

    virtual void update(float p_dt);
    virtual void render(const glm::mat4 &p_mProj, const glm::mat4 &p_mView){};
    virtual void renderWithBounds(const glm::mat4 &p_mProj, const glm::mat4 &p_mView){};

    virtual void initComponents();

    virtual std::string getName();

    virtual void setScale(const glm::vec3 &p_vNewSc);
    virtual void setRotate(const glm::vec3 &p_vNewRo);
    virtual void setTranslate(const glm::vec3 &p_vNewTr);
    virtual glm::mat4 getTransformation();

    virtual glm::vec3 getScale();
    virtual glm::vec3 getRotate();
    virtual glm::vec3 getTranslate();

    virtual glm::vec3 getGlobalScale();
    virtual glm::vec3 getGlobalRotate();
    virtual glm::vec3 getGlobalTranslate();

    virtual bool isTransformDirty();

    virtual Node *getParent();

    virtual void addChild(Node *p_pNode);
    virtual std::vector<Node *> getImmediateChildren();

    virtual void addComponent(ComponentBase *p_pCompBase);
    virtual ComponentBase *GetComponent(std::string p_pCompID);

    virtual float calculateCentreToFurthestPoint();
    virtual glm::vec3 getNodeHierarchyCentre();

protected:
    CompMap m_ComponentMap;

    std::string m_sName = "";

    Transform *m_pTransform = nullptr;

    Node *m_pParent = nullptr;
    std::vector<Node *> m_vpChildren;
    bool m_bIsAddingChildren = true;

    static int s_iNodeCount;
};