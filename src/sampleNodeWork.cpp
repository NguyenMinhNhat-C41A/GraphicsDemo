#include "sampleNodeWork.h"

SampleNodeWork::~SampleNodeWork()
{
    FactoryMethodsManager::DestroyInstance();
    EffectManager::destroyInstance();
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
    FactoryMethodsManager::Instance()->registerNodeFactoryMethod("DynamicDebugCube", DynamicDebugCube::Factory);

    FactoryMethodsManager::Instance()->registerComponentFactoryMethod("GOC_BoundingSphere", BoundingSphere::Factory);
    FactoryMethodsManager::Instance()->registerComponentFactoryMethod("GOC_Effect", ComponentEffect::Factory);

    //_______________________________________________________________________________________________________________________________________________________//

    //     // int width = RandomNumberGenerator::getRandomNumber(6, 7);
    //     // int height = RandomNumberGenerator::getRandomNumber(6, 7);
    //
    //     //  RandomNumberGenerator::getRandomNumber(121, 196)
    //     // glm::vec3(RandomNumberGenerator::getRandomNumber(-70, 70), RandomNumberGenerator::getRandomNumber(-70, 70), RandomNumberGenerator::getRandomNumber(-70, 70))
    //     // glm::vec3(RandomNumberGenerator::getRandomNumber(1, 5), RandomNumberGenerator::getRandomNumber(1, 5), RandomNumberGenerator::getRandomNumber(1, 5))

    //_______________________________________________________________________________________________________________________________________________________//

    glm::vec2 hBounds = glm::vec2(-256, 256);
    glm::vec2 vBounds = glm::vec2(-128, 128);

    for (int i = 0; i < RandomNumberGenerator::getRandomNumber(81, 121); i++)
    {
        Node *rootCube01 = FactoryMethodsManager::Instance()->createNode("debugCube.xml");
        Scene::Instance()->addNode(rootCube01);

        DebugCube *childCube01 = new DebugCube("ChildCube1-" + std::to_string(i),
                                               glm::vec3(RandomNumberGenerator::getRandomNumber(1, 5) / 5.0f),
                                               glm::vec3(RandomNumberGenerator::getRandomNumber(0, 359), RandomNumberGenerator::getRandomNumber(0, 359), RandomNumberGenerator::getRandomNumber(0, 359)),
                                               glm::vec3(RandomNumberGenerator::getRandomNumber(1, 4), RandomNumberGenerator::getRandomNumber(1, 4), RandomNumberGenerator::getRandomNumber(1, 4)));

        BoundingSphere *boSphrChild01 = dynamic_cast<BoundingSphere *>(BoundingSphere::createComponent(childCube01));
        boSphrChild01->setDynamicUpdate(false);
        rootCube01->addChild(childCube01);
    }

    Node *ddbc = FactoryMethodsManager::Instance()->createNode("dynamicDebugCube.xml");
    Scene::Instance()->addDynamicNode(ddbc);

    Node *ddbc2 = FactoryMethodsManager::Instance()->createNode("dynamicDebugCube.xml");
    Scene::Instance()->addDynamicNode(ddbc2);

    for (auto node : Scene::Instance()->getNodes())
    {
        node->initComponents();
    }
    Scene::Instance()->initQuadtree();
}

void SampleNodeWork::update(float dt)
{
    Scene::Instance()->update(dt);
    EffectManager::Instance()->updateEffectsEmittors(dt);
    Scene::Instance()->getCamera()->update(dt);
    this->counter += dt;

    if (this->m_pApp->isKeyDown('Q'))
    {
        if (!this->isKeyDownQ)
        {
            this->isKeyDownQ = true;
        }
    }
    else
    {
        if (this->isKeyDownQ)
        {
            this->isKeyDownQ = false;
            this->isRenderWithBounds = !this->isRenderWithBounds;
        }
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

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    EffectManager::Instance()->renderEffectsEmittors(projMatrix, viewMatrix);
    glDisable(GL_BLEND);
}