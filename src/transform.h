#pragma once

#include "../wolf/wolf.h"

class Transform
{
public:
    Transform();
    ~Transform();

    void setScale(const glm::vec3 &p_vNewSc);
    void setRotate(const glm::vec3 &p_vNewRo);
    void setTranslate(const glm::vec3 &p_vNewTr);
    glm::mat4 getTransformation();

    glm::vec3 getScale();
    glm::vec3 getRotate();
    glm::vec3 getTranslate();

    bool getDirtyBit();

private:
    glm::vec3 m_vScale = glm::vec3(1.0f);
    glm::vec3 m_vRotate = glm::vec3(0.0f);
    glm::vec3 m_vTranslate = glm::vec3(0.0f);

    glm::mat4 m_mTransform = glm::mat4(0.0f);

    bool m_bDirty = false;
};
