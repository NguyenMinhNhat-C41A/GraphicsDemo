#include "scene.h"

Scene *Scene::s_pScene = nullptr;

void Scene::createInstance(wolf::App *p_pApp)
{
    assert(Scene::s_pScene == nullptr);
    Scene::s_pScene = new Scene(p_pApp);
}
void Scene::destroyInstance()
{
    assert(Scene::s_pScene != nullptr);
    delete Scene::s_pScene;
}
Scene *Scene::Instance()
{
    return Scene::s_pScene;
}

void Scene::addNode(Node *p_pNode)
{
    this->m_vpNodes.push_back(p_pNode);
}

std::vector<Node *> Scene::getNodes()
{
    return this->m_vpNodes;
}

void Scene::addDynamicNode(Node *p_pDynamicNode)
{
    this->m_vpDynamicNodes.push_back(p_pDynamicNode);
}

std::vector<Node *> Scene::getDynamicNodes()
{
    return this->m_vpDynamicNodes;
}

void Scene::setCamera(FirstPersonCamera *p_pCamera)
{
    this->m_pCamera = p_pCamera;
}

FirstPersonCamera *Scene::getCamera()
{
    return this->m_pCamera;
}

void Scene::update(float dt)
{

    for (auto node : m_vpNodes)
    {
        node->update(dt);
    }

    for (auto dynamicNode : this->m_vpDynamicNodes)
    {
        dynamicNode->update(dt);
    }

    if (this->m_pApp->isKeyDown('E'))
    {
        if (!this->isKeyDownE)
        {
            this->isKeyDownE = true;
        }
    }
    else
    {
        if (this->isKeyDownE)
        {
            this->isKeyDownE = false;
            this->isRenderAllNodes = !this->isRenderAllNodes;
        }
    }

    this->m_vpInViewNodes = FrustumCuller::getInViewNodes(this->m_pCamera->getFrustum(), this->m_pQuadtree);
}
void Scene::render(const glm::mat4 &p_mProj, const glm::mat4 &p_mView)
{
    // std::cout << "SCENE - NUM_INVIEW_NODES: " << this->m_vpInViewNodes.size() << std::endl;
    for (auto node : this->m_vpInViewNodes)
    {
        node->render(p_mProj, p_mView);
    }

    for (auto dynamicNode : this->m_vpDynamicNodes)
    {
        dynamicNode->render(p_mProj, p_mView);
    }
}

void Scene::renderWithBounds(const glm::mat4 &p_mProj, const glm::mat4 &p_mView)
{
    // std::cout << "SCENE - NUM_NODES: " << this->m_vpNodes.size() << std::endl;
    for (auto node : this->m_vpNodes)
    {
        node->renderWithBounds(p_mProj, p_mView);
    }

    for (auto dynamicNode : this->m_vpDynamicNodes)
    {
        dynamicNode->renderWithBounds(p_mProj, p_mView);
    }

    this->m_pQuadtree->renderBounds(p_mProj, p_mView);
}

void Scene::initQuadtree()
{
    // std::cout << "SCENE - INIT" << std::endl;
    this->m_pQuadtree->initQuadtree();
}

//--------------------------------------------------------------------------------
//
// PRIVATE METHODS
//
//--------------------------------------------------------------------------------

Scene::Scene(wolf::App *p_pApp)
{
    this->m_pQuadtree = new Quadtree(512.0f, 256.0f, 512.0f);
    this->m_pApp = p_pApp;
}

Scene::~Scene()
{
    for (auto node : this->m_vpNodes)
    {
        delete node;
        node = nullptr;
    }
    this->m_vpNodes.clear();
    delete this->m_pQuadtree;
    this->m_pQuadtree = nullptr;

    delete this->m_pCamera;
    this->m_pCamera = nullptr;

    this->m_pApp = nullptr;
}
