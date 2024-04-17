#pragma once
#include "../wolf/wolf.h"
#include "componentEffect.h"
#include "emittor.h"
#include <vector>
class ComponentEffect;
class Emittor;
class EffectManager
{
public:
    static void createInstance(wolf::App *p_pApp);
    static void destroyInstance();
    static EffectManager *Instance();

    void addEmittor(Emittor *p_pEmittor);
    void removeEmittor(Emittor *p_pEmittor);

    void updateEmittors(float p_dt);
    //void renderEmittors(const glm::mat4 &p_mProj, const glm::mat4 &p_mView);
    void renderOpaqueEmittors(const glm::mat4 &p_mProj, const glm::mat4 &p_mView);
    void renderTransparentEmittors(const glm::mat4 &p_mProj, const glm::mat4 &p_mView);

private:
    EffectManager(wolf::App *p_pApp);
    ~EffectManager();

        static EffectManager *s_pEffectManager;

    std::vector<Emittor *> m_vpOpaqueEmittors;
    std::vector<Emittor *> m_vpTransparentEmittors;
    std::vector<Emittor *> m_vpEmittors;
};
