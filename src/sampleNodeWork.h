#pragma once
#include "../wolf/wolf.h"
#include "../samplefw/Sample.h"
#include "../samplefw/scene.h"
#include "../samplefw/FirstPersonCamera.h"

#include "IOManager.h"
#include "effectManager.h"
#include "factoryMethodsManager.h"
#include "rng.h"

#include "debugCube.h"
#include "dynamicDebugCube.h"
#include "boundingSphere.h"
#include "componentEffect.h"
#include "skybox.h"
class SampleNodeWork : public Sample
{
public:
    SampleNodeWork(wolf::App *pApp) : Sample(pApp, "NodeWork"){};
    ~SampleNodeWork();

    void init() override;
    void update(float dt) override;
    void render(int width, int height) override;

private:
    double counter = 0.0f;

    bool isRenderWithBounds = 0.0f;

    bool isKeyDownQ = false;

    Skybox *m_bSkybox = nullptr;
};