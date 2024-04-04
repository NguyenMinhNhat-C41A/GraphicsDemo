#pragma once
#include "../wolf/wolf.h"
#include "../src/node.h"
#include "quadtree.h"
#include "FirstPersonCamera.h"
#include "../src/frustumCuller.h"
class Quadtree;
class Scene
{
public:
    static void createInstance(wolf::App *p_pApp);
    static void destroyInstance();
    static Scene *Instance();
    void update(float dt);
    void render(const glm::mat4 &p_mProj, const glm::mat4 &p_mView);

    void renderWithBounds(const glm::mat4 &p_mProj, const glm::mat4 &p_mView);

    void initQuadtree();

    void addNode(Node *p_pNode);
    std::vector<Node *> getNodes();

    void addDynamicNode(Node *p_pDynamicNode);
    std::vector<Node *> getDynamicNodes();

    void setCamera(FirstPersonCamera *p_pCamera);
    FirstPersonCamera *getCamera();

private:
    Scene(wolf::App *p_pApp);
    ~Scene();

    static Scene *s_pScene;

    Quadtree *m_pQuadtree = nullptr;

    std::vector<Node *> m_vpNodes;
    std::vector<Node *> m_vpDynamicNodes;
    std::vector<Node *> m_vpInViewNodes;

    FirstPersonCamera *m_pCamera = nullptr;

    wolf::App *m_pApp = nullptr;

    float m_fCounter = 0.0f;

    bool isRenderAllNodes = false;
    bool isKeyDownE = false;
};