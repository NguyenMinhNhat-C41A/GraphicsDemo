#pragma once
#include "../wolf/wolf.h"
#include "componentEffect.h"
#include <vector>
class ComponentEffect;
class EffectManager
{
public:
    static void createInstance(wolf::App *p_pApp);
    static void destroyInstance();
    static EffectManager *Instance();

    void addEffect(ComponentEffect *compEffect);
    void removeEffect(ComponentEffect *compEffect);

    void updateEffectsEmittors(float p_dt);
    void renderEffectsEmittors(const glm::mat4 &p_mProj, const glm::mat4 &p_mView);

private:
    EffectManager(wolf::App *p_pApp);
    ~EffectManager();
    static EffectManager *s_pEffectManager;

    std::vector<ComponentEffect *> m_vpEffects;
};
