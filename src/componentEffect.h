#pragma once
#include "../wolf/wolf.h"
#include "transform.h"
#include "componentBase.h"
#include "effectManager.h"
#include "emissionMode.h"
#include "emittor.h"
#include "../thirdparty/tinyxml2/tinyxml2.h"

class Emittor;
class EffectManager;

class ComponentEffect : public ComponentBase
{

    friend Emittor;
    friend EffectManager;

public:
    static ComponentBase *createComponent(Node *p_pCompNode);
    static ComponentBase *Factory(Node *p_pCompNode, tinyxml2::XMLNode *p_pXMLNode);

    ~ComponentEffect();

    virtual std::string ComponentID() override { return "GOC_Effect"; };

    virtual void init() override;
    virtual void update(float dt) override;

    void addEmittor(Emittor *p_pEmittor);
    void updateEmittors(float p_dt);
    void renderEmittors(const glm::mat4 &p_mProj, const glm::mat4 &p_mView);

    glm::vec3 getGlobalTranslate();

private:
    ComponentEffect(Node *p_pCompNode);
    Transform *m_pTransform = nullptr;
    std::vector<Emittor *> m_vEmittors;
};