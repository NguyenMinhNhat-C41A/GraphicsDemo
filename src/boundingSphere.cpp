#include "boundingSphere.h"

const CubeVertex gs_BoundingSphereVertexCoords[] = {
    // ClounterClockwise from Upper Left

    // xz
    {0.0f, 0.0f, 0.5f},
    {0.25f, 0.0f, 0.433f},

    {0.25f, 0.0f, 0.433f},
    {0.433f, 0.0f, 0.25f},

    {0.433f, 0.0f, 0.25f},
    {0.5f, 0.0f, 0.0f},

    {0.5f, 0.0f, 0.0f},
    {0.433f, 0.0f, -0.25f},

    {0.433f, 0.0f, -0.25f},
    {0.25f, 0.0f, -0.433f},

    {0.25f, 0.0f, -0.433f},
    {0.0f, 0.0f, -0.5f},

    {0.0f, 0.0f, -0.5f},
    {-0.25f, 0.0f, -0.433f},

    {-0.25f, 0.0f, -0.433f},
    {-0.433f, 0.0f, -0.25f},

    {-0.433f, 0.0f, -0.25f},
    {-0.5f, 0.0f, 0.0f},

    {-0.5f, 0.0f, 0.0f},
    {-0.433f, 0.0f, 0.25f},

    {-0.433f, 0.0f, 0.25f},
    {-0.25f, 0.0f, 0.433f},

    {-0.25f, 0.0f, 0.433f},
    {0.0f, 0.0f, 0.5f},

    // yz
    {0.0f, 0.0f, 0.5f},
    {0.0f, 0.25f, 0.433f},

    {0.0f, 0.25f, 0.433f},
    {0.0f, 0.433f, 0.25f},

    {0.0f, 0.433f, 0.25f},
    {0.0f, 0.5f, 0.0f},

    {0.0f, 0.5f, 0.0f},
    {0.0f, 0.433f, -0.25f},

    {0.0f, 0.433f, -0.25f},
    {0.0f, 0.25f, -0.433f},

    {0.0f, 0.25f, -0.433f},
    {0.0f, 0.0f, -0.5f},

    {0.0f, 0.0f, -0.5f},
    {0.0f, -0.25f, -0.433f},

    {0.0f, -0.25f, -0.433f},
    {0.0f, -0.433f, -0.25f},

    {0.0f, -0.433f, -0.25f},
    {0.0f, -0.5f, 0.0f},

    {0.0f, -0.5f, 0.0f},
    {0.0f, -0.433f, 0.25f},

    {0.0f, -0.433f, 0.25f},
    {0.0f, -0.25f, 0.433f},

    {0.0f, -0.25f, 0.433f},
    {0.0f, 0.0f, 0.5f},
};

ComponentBase *BoundingSphere::createComponent(Node *p_pCompNode)
{
    BoundingSphere *pBoSphrComp = new BoundingSphere(p_pCompNode);
    p_pCompNode->addComponent(pBoSphrComp);
    return pBoSphrComp;
}

ComponentBase *BoundingSphere::Factory(Node *p_pCompNode, tinyxml2::XMLNode *p_pXMLNode)
{
    BoundingSphere *pBoSphrComp = new BoundingSphere(p_pCompNode);
    return pBoSphrComp;
}

BoundingSphere::BoundingSphere(Node *p_pCompNode) : BoundingVolume(p_pCompNode)
{
    if (!m_pProgram)
    {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        m_pProgram = wolf::ProgramManager::CreateProgram("data/nodeWorkBounds.vsh", "data/nodeWorkBounds.fsh");
        m_pVB = wolf::BufferManager::CreateVertexBuffer(gs_BoundingSphereVertexCoords, sizeof(CubeVertex) * 48);

        m_pDecl = new wolf::VertexDeclaration();
        m_pDecl->Begin();
        m_pDecl->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
        m_pDecl->SetVertexBuffer(m_pVB);
        m_pDecl->End();
    }
}

BoundingSphere::~BoundingSphere()
{
}

void BoundingSphere::calculateBounds()
{

    this->m_fRadius = this->m_pCompNode->calculateCentreToFurthestPoint();

    std::vector<Node *> immediateChildren = this->m_pCompNode->getImmediateChildren();

    glm::vec3 centre = this->m_pCompNode->getNodeHierarchyCentre();

    float maxRadius = this->m_fRadius;
    float distToNode = glm::distance(centre, this->m_pCompNode->getGlobalTranslate());
    maxRadius = distToNode + this->m_fRadius;

    for (auto childNode : this->m_pCompNode->getImmediateChildren())
    {
        glm::vec3 childNodePos = childNode->getNodeHierarchyCentre();

        float distToChildNode = glm::distance(childNodePos, centre);
        float childBoSphrRad = 0.0f;

        ComponentBase *childBoundingSphereComp = childNode->GetComponent(this->ComponentID());
        if (childBoundingSphereComp)
        {
            BoundingSphere *childBoundingSphere = dynamic_cast<BoundingSphere *>(childBoundingSphereComp);
            childBoSphrRad = childBoundingSphere->getRadius();
        }
        maxRadius = std::max(maxRadius, childBoSphrRad + distToChildNode);
    }
    this->m_fRadius = maxRadius;
}

bool BoundingSphere::intersects(BoundingVolume *p_pBV)
{
    if (p_pBV->ComponentID() == "GOC_BoundingBox")
    {
    }
    return false;
}

bool BoundingSphere::intersectsPoint(const glm::vec3 &p_Point)
{

    glm::vec3 centre = this->getGlobalCentre();
    return (pow((p_Point.x - centre.x), 2) + pow((p_Point.y - centre.y), 2) + pow((p_Point.z - centre.z), 2)) <= pow(this->m_fRadius, 2);
}

bool BoundingSphere::isIntersectingOrBeforePlane(const Plane &p_Plane)
{
    // std::cout << "BOSPHR - PLANE_TAG: " << p_Plane.tag << std::endl;
    // std::cout << "BOSPHR - PLANE_NORMAL: " << p_Plane.normal.x << ", " << p_Plane.normal.y << ", " << p_Plane.normal.z << std::endl;
    float signedDistance = glm::dot(p_Plane.normal, this->getGlobalCentre()) + p_Plane.distance;

    bool result = signedDistance > -this->m_fRadius;

    // std::cout << "BOSPHR - IOBCHECK: " << result << std::endl;
    return result;
}

void BoundingSphere::init()
{
    this->m_fRadius = this->m_pCompNode->calculateCentreToFurthestPoint();
    this->calculateBounds();
}

void BoundingSphere::update(float dt)
{
    // std::cout << "BOSPHR - RADIUS: " << this->m_fRadius << std::endl;
    if (this->m_bIsDynamicUpdate)
    {
        if (this->m_bIsDirtyImmediateChildrenCount || this->m_bIsDirtyNodeTransform)
        {
            this->calculateBounds();
        }

        if (this->m_bIsDirtyImmediateChildrenCount)
        {
            this->m_bIsDirtyImmediateChildrenCount = false;
        }

        if (this->m_bIsDirtyNodeTransform)
        {

            this->m_bIsDirtyNodeTransform = false;
        }
    }
}

void BoundingSphere::render(const glm::mat4 &p_mProj, const glm::mat4 &p_mView)
{
    // std::cout << "BOSPHR - RENDER_TEST_SCALE: " << this->m_pTransform->getScale().x * this->m_fRadius << std::endl;

    glm::mat4 mWorld = glm::translate(glm::mat4(1.0f), this->getGlobalCentre()) *
                       glm::scale(glm::mat4(1.0f), this->m_pTransform->getScale() * this->m_fRadius * 2.0f);
    this->m_pProgram->SetUniform("projection_view", p_mProj * p_mView);
    this->m_pProgram->SetUniform("world", mWorld);
    this->m_pProgram->Bind();
    this->m_pDecl->Bind();
    glDrawArrays(GL_LINES, 0, 48);
}

void BoundingSphere::setRadius(float rad)
{
    this->m_fRadius = rad;
}

float BoundingSphere::getRadius()
{
    return this->m_fRadius;
}

void BoundingSphere::setComponentNode(Node *p_pCompNode)
{
    if (!this->m_pCompNode)
    {
        this->m_pCompNode = p_pCompNode;
    }
}
