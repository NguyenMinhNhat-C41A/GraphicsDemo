#pragma once
#include <string>
#include "node.h"
#include <iostream>
class Node;
class ComponentBase
{
public:
    friend Node;

    virtual std::string ComponentID() = 0;

    Node *getComponentNode()
    {
        return this->m_pCompNode;
    };

protected:
    ComponentBase(Node *p_pCompNode);
    ~ComponentBase(){};

    virtual void init() = 0;

    virtual void update(float dt) = 0;

    void setComponentNode(Node *p_pCompNode)
    {
        if (!this->m_pCompNode)
            this->m_pCompNode = p_pCompNode;
    };

    void nodeTransformDirty()
    {
        this->m_bIsDirtyNodeTransform = true;
    }

    void nodeImmediateChildrenCountDirty()
    {
        this->m_bIsDirtyImmediateChildrenCount = true;
    }

    Node *m_pCompNode = nullptr;

    bool m_bIsDirtyNodeTransform = false;
    bool m_bIsDirtyImmediateChildrenCount = false;
};