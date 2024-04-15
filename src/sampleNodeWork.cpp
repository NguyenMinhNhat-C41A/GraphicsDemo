#include "sampleNodeWork.h"

SampleNodeWork::~SampleNodeWork()
{
    FactoryMethodsManager::DestroyInstance();
    EffectManager::destroyInstance();
    IOManager::destroyInstance();
    Scene::destroyInstance();
    delete this->m_bSkybox;
    this->m_bSkybox = nullptr;
}

void SampleNodeWork::init()
{
    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(this->m_pApp->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //-----------------------------------
    // INIT SINGLETONS
    //-----------------------------------

    Scene::createInstance(this->m_pApp);
    IOManager::createInstance(this->m_pApp);
    EffectManager::createInstance(this->m_pApp);
    FactoryMethodsManager::CreateInstance();

    //-----------------------------------
    // SCENE SINGLETON SETUP
    //-----------------------------------

    Scene::Instance()->setCamera(new FirstPersonCamera(m_pApp));
    this->m_bSkybox = new Skybox();

    //-----------------------------------
    // FACTORYMETHODSMANAGER SINGLETON SETUP
    //-----------------------------------
    FactoryMethodsManager::Instance()->registerNodeFactoryMethod("DebugCube", DebugCube::Factory);

    FactoryMethodsManager::Instance()->registerComponentFactoryMethod("GOC_BoundingSphere", BoundingSphere::Factory);
    FactoryMethodsManager::Instance()->registerComponentFactoryMethod("GOC_Effect", ComponentEffect::Factory);
    FactoryMethodsManager::Instance()->registerComponentFactoryMethod("GOC_Orbitor", ComponentOrbitor::Factory);

    glm::vec2 hBounds = glm::vec2(-256, 256);
    glm::vec2 vBounds = glm::vec2(-128, 128);

    for (int i = 0; i < RandomNumberGenerator::getRandomNumber(64, 80); i++)
    {

        Node *rootCube = FactoryMethodsManager::Instance()->createNode("xmlDataFiles/debugCube.xml");
        Scene::Instance()->addNode(rootCube);
        Node *childCube = FactoryMethodsManager::Instance()->createNode("xmlDataFiles/debugCubeChild.xml");
        rootCube->addChild(childCube);
    }

    Node *dynamicCube01 = FactoryMethodsManager::Instance()->createNode("xmlDataFiles/dynamicDebugCube.xml");
    Scene::Instance()->addDynamicNode(dynamicCube01);

    Node *dynamicCube02 = FactoryMethodsManager::Instance()->createNode("xmlDataFiles/dynamicDebugCube.xml");
    Scene::Instance()->addDynamicNode(dynamicCube02);

    for (auto node : Scene::Instance()->getNodes())
    {
        node->initComponents();
    }
    Scene::Instance()->initQuadtree();
}

void SampleNodeWork::update(float dt)
{
    Scene::Instance()->update(dt);
    IOManager::Instance()->update(dt);
    EffectManager::Instance()->updateEmittors(dt);

    Scene::Instance()->getCamera()->update(dt);
    this->counter += dt;

    if (IOManager::Instance()->isButtonReleased('Q'))
    {
        this->isRenderWithBounds = !this->isRenderWithBounds;
    }
}

void SampleNodeWork::render(int width, int height)
{

    glClearColor(0.3f, 0.3f, 0.3f, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 projMatrix = Scene::Instance()->getCamera()->getProjMatrix();

    glm::mat4 viewMatrix = Scene::Instance()->getCamera()->getViewMatrix();

    this->m_bSkybox->render(projMatrix, viewMatrix);

    if (isRenderWithBounds)
    {

        Scene::Instance()->renderWithBounds(projMatrix, viewMatrix);
    }
    else
    {
        Scene::Instance()->render(projMatrix, viewMatrix);
    }

    EffectManager::Instance()->renderOpaqueEmittors(projMatrix, viewMatrix);

    EffectManager::Instance()->renderTransparentEmittors(projMatrix, viewMatrix);
}