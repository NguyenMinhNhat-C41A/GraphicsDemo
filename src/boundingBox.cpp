#include "boundingBox.h"

const CubeVertex gs_BoundingBoxVertexCoords[] = {
    // ClounterClockwise from Upper Left

    //
    {-0.5f, 0.5f, 0.5f},
    {-0.5f, -0.5f, 0.5f},

    {0.5f, 0.5f, 0.5f},
    {0.5f, -0.5f, 0.5f},

    {-0.5f, 0.5f, 0.5f},
    {0.5f, 0.5f, 0.5f},

    {-0.5f, -0.5f, 0.5f},
    {0.5f, -0.5f, 0.5f},

    //
    {-0.5f, 0.5f, -0.5f},
    {-0.5f, -0.5f, -0.5f},

    {0.5f, 0.5f, -0.5f},
    {0.5f, -0.5f, -0.5f},

    {-0.5f, 0.5f, -0.5f},
    {0.5f, 0.5f, -0.5f},

    {-0.5f, -0.5f, -0.5f},
    {0.5f, -0.5f, -0.5f},

    //
    {-0.5f, 0.5f, 0.5f},
    {-0.5f, 0.5f, -0.5f},

    {-0.5f, -0.5f, 0.5f},
    {-0.5f, -0.5f, -0.5f},

    {0.5f, 0.5f, 0.5f},
    {0.5f, 0.5f, -0.5f},

    {0.5f, -0.5f, 0.5f},
    {0.5f, -0.5f, -0.5f},
};

ComponentBase *BoundingBox::createComponent(Node *p_pCompNode)
{
    BoundingBox *pBBoxComp = new BoundingBox(p_pCompNode);
    p_pCompNode->addComponent(pBBoxComp);
    return pBBoxComp;
}

BoundingBox::BoundingBox(Node *p_pCompNode) : BoundingVolume(p_pCompNode)
{
    if (!m_pProgram)
    {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        m_pProgram = wolf::ProgramManager::CreateProgram("data/nodeWorkBounds.vsh", "data/nodeWorkBounds.fsh");
        m_pVB = wolf::BufferManager::CreateVertexBuffer(gs_BoundingBoxVertexCoords, sizeof(CubeVertex) * 24);

        m_pDecl = new wolf::VertexDeclaration();
        m_pDecl->Begin();
        m_pDecl->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
        m_pDecl->SetVertexBuffer(m_pVB);
        m_pDecl->End();
    }
}

BoundingBox::~BoundingBox()
{
    delete this->m_pDecl;
    this->m_pDecl = nullptr;
    wolf::ProgramManager::DestroyProgram(this->m_pProgram);
    this->m_pProgram = nullptr;
    wolf::BufferManager::DestroyBuffer(this->m_pVB);
    this->m_pVB = nullptr;
}

void BoundingBox::init()
{
    this->calculateBounds();
}

void BoundingBox::update(float p_dt)
{
    std::cout << "BBOX - UPDATE" << std::endl;
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

void BoundingBox::render(const glm::mat4 &p_mProj, const glm::mat4 &p_mView)
{

    glm::mat4 mWorld = glm::translate(glm::mat4(1.0f), this->getGlobalCentre()) * glm::scale(glm::mat4(1.0f), this->m_pTransform->getScale());
    this->m_pProgram->SetUniform("projection_view", p_mProj * p_mView);
    this->m_pProgram->SetUniform("world", mWorld);
    this->m_pProgram->Bind();
    this->m_pDecl->Bind();
    glDrawArrays(GL_LINES, 0, 24);
}

void BoundingBox::calculateBounds()
{
}

bool BoundingBox::intersects(BoundingVolume *p_pBV)
{
    if (p_pBV->ComponentID() == "GOC_BoundingSphere")
    {
        BoundingSphere *boSphr = dynamic_cast<BoundingSphere *>(p_pBV);

        return BoundingVolumeIntersectCalculator::isIntersectingBoxSphere(this, boSphr);
    }
    return false;
}

bool BoundingBox::intersectsPoint(const glm::vec3 &p_Point)
{
    glm::vec3 globalCentre = this->getGlobalCentre();

    float xMax = globalCentre.x + this->getWidth();
    float xMin = globalCentre.x - this->getWidth();

    float yMax = globalCentre.y + this->getHeight();
    float yMin = globalCentre.y - this->getHeight();

    float zMax = globalCentre.z + this->getLength();
    float zMin = globalCentre.z - this->getLength();

    return (p_Point.x <= xMax && p_Point.x >= xMin) &&
           (p_Point.y <= yMax && p_Point.y >= yMin) &&
           (p_Point.z <= zMax && p_Point.z >= zMin);
}

bool BoundingBox::isIntersectingOrBeforePlane(const Plane &p_Plane)
{
    int nx = p_Plane.normal.x > 0.0f;

    int ny = p_Plane.normal.y > 0.0f;

    int nz = p_Plane.normal.z > 0.0f;

    float dot01 = glm::dot(this->getMinMaxCoords(nx, ny, nz), p_Plane.normal);
    // std::cout << "FRCL - DIST01: " << dist01 << std::endl;
    if (dot01 < -p_Plane.distance)
    {
        // std::cout << "FRCL - QNODE_BEHIND_PLANE" << std::endl;
        return false;
    }

    return true;
}

void BoundingBox::setWidth(float p_fWidth)
{
    glm::vec3 oldScale = this->m_pTransform->getScale();
    this->m_pTransform->setScale(glm::vec3(p_fWidth, oldScale.y, oldScale.z));
}

float BoundingBox::getWidth()
{
    return this->m_pTransform->getScale().x;
}

void BoundingBox::setHeight(float p_fHeight)
{
    glm::vec3 oldScale = this->m_pTransform->getScale();
    this->m_pTransform->setScale(glm::vec3(oldScale.x, p_fHeight, oldScale.z));
}
float BoundingBox::getHeight()
{
    return this->m_pTransform->getScale().y;
}

void BoundingBox::setLength(float p_fLength)
{
    glm::vec3 oldScale = this->m_pTransform->getScale();
    this->m_pTransform->setScale(glm::vec3(oldScale.x, oldScale.y, p_fLength));
}

float BoundingBox::getLength()
{
    return this->m_pTransform->getScale().z;
}

glm::vec3 BoundingBox::getMinMaxCoords(int p_iX, int p_iY, int p_iZ)
{
    glm::vec3 globalCentre = this->getGlobalCentre();
    glm::vec3 result = glm::vec3(0.0f);

    if (p_iX == 1)
    {
        result.x = globalCentre.x + this->getWidth() * 0.5f;
    }
    else
    {
        result.x = globalCentre.x - this->getWidth() * 0.5f;
    }

    if (p_iY == 1)
    {
        result.y = globalCentre.y + this->getHeight() * 0.5f;
    }
    else
    {
        result.y = globalCentre.y - this->getHeight() * 0.5f;
    }

    if (p_iZ == 1)
    {
        result.z = globalCentre.z + this->getLength() * 0.5f;
    }
    else
    {
        result.z = globalCentre.z - this->getLength() * 0.5f;
    }

    return result;
}