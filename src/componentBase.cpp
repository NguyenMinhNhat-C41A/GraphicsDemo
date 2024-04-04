#include "componentBase.h"

ComponentBase::ComponentBase(Node *p_pCompNode)
{
    if (!this->m_pCompNode)
        this->m_pCompNode = p_pCompNode;
};