#include "transform.h"
Transform::Transform() {}
Transform::~Transform() {}

void Transform::setScale(const glm::vec3 &p_vNewSc)
{
    this->m_vScale = p_vNewSc;
    this->m_bDirty = true;
}
void Transform::setRotate(const glm::vec3 &p_vNewRo)
{
    this->m_vRotate = p_vNewRo;
    this->m_bDirty = true;
}
void Transform::setTranslate(const glm::vec3 &p_vNewTr)
{
    this->m_vTranslate = p_vNewTr;
    this->m_bDirty = true;
}
glm::mat4 Transform::getTransformation()
{
    if (this->m_bDirty)
    {
        glm::mat4 mSc = glm::scale(glm::mat4(1.0f), this->m_vScale);
        glm::mat4 mRo = glm::rotate(glm::mat4(1.0f), glm::radians(this->m_vRotate.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
                        glm::rotate(glm::mat4(1.0f), glm::radians(this->m_vRotate.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
                        glm::rotate(glm::mat4(1.0f), glm::radians(this->m_vRotate.z), glm::vec3(0.0f, 0.0f, 1.0f));
        glm::mat4 mTr = glm::translate(glm::mat4(1.0f), this->m_vTranslate);
        this->m_mTransform = mTr * mRo * mSc;
        this->m_bDirty = false;
    }

    return this->m_mTransform;
}

glm::vec3 Transform::getScale()
{
    return this->m_vScale;
}
glm::vec3 Transform::getRotate()
{
    return this->m_vRotate;
}
glm::vec3 Transform::getTranslate()
{
    return this->m_vTranslate;
}

bool Transform::getDirtyBit()
{
    return this->m_bDirty;
}