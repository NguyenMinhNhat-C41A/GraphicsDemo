#include "skybox.h"
static wolf::VertexBuffer *m_pVB = nullptr;
static wolf::VertexDeclaration *m_pDecl = nullptr;
static wolf::Program *m_pProgram = nullptr;

struct Vertex
{
    GLfloat x, y, z;
};

static const Vertex cubeVertices[] = {

    // Front face
    {-0.5f, -0.5f, 0.5f},
    {0.5f, -0.5f, 0.5f},
    {0.5f, 0.5f, 0.5f},
    {0.5f, 0.5f, 0.5f},
    {-0.5f, 0.5f, 0.5f},
    {-0.5f, -0.5f, 0.5f},

    // Back face
    {-0.5f, -0.5f, -0.5f},
    {0.5f, -0.5f, -0.5f},
    {0.5f, 0.5f, -0.5f},
    {0.5f, 0.5f, -0.5f},
    {-0.5f, 0.5f, -0.5f},
    {-0.5f, -0.5f, -0.5f},

    // Left face
    {-0.5f, -0.5f, -0.5f},
    {-0.5f, -0.5f, 0.5f},
    {-0.5f, 0.5f, 0.5f},
    {-0.5f, 0.5f, 0.5f},
    {-0.5f, 0.5f, -0.5f},
    {-0.5f, -0.5f, -0.5f},

    // Right face
    {0.5f, -0.5f, -0.5f},
    {0.5f, -0.5f, 0.5f},
    {0.5f, 0.5f, 0.5f},
    {0.5f, 0.5f, 0.5f},
    {0.5f, 0.5f, -0.5f},
    {0.5f, -0.5f, -0.5f},

    // Top face
    {-0.5f, 0.5f, 0.5f},
    {0.5f, 0.5f, 0.5f},
    {0.5f, 0.5f, -0.5f},
    {0.5f, 0.5f, -0.5f},
    {-0.5f, 0.5f, -0.5f},
    {-0.5f, 0.5f, 0.5f},

    // Bottom face
    {-0.5f, -0.5f, -0.5f},
    {0.5f, -0.5f, -0.5f},
    {0.5f, -0.5f, 0.5f},
    {0.5f, -0.5f, 0.5f},
    {-0.5f, -0.5f, 0.5f},
    {-0.5f, -0.5f, -0.5f},
};

Skybox::Skybox()
{
    if (!m_pProgram)
    {
        m_pProgram = wolf::ProgramManager::CreateProgram("data/skybox.vsh", "data/skybox.fsh");
        m_pVB = wolf::BufferManager::CreateVertexBuffer(cubeVertices, sizeof(Vertex) * 36);
        m_pDecl = new wolf::VertexDeclaration();
        m_pDecl->Begin();
        m_pDecl->AppendAttribute(wolf::AT_Position, 3, wolf::CT_Float);
        m_pDecl->SetVertexBuffer(m_pVB);
        m_pDecl->End();
    }

    const int skyboxTexPack = 2;
    std::vector<std::string> paths = {
        "data/textures/SkyboxRight" + std::to_string(skyboxTexPack) + ".png",
        "data/textures/SkyboxLeft" + std::to_string(skyboxTexPack) + ".png",
        "data/textures/SkyboxTop" + std::to_string(skyboxTexPack) + ".png",
        "data/textures/SkyboxBottom" + std::to_string(skyboxTexPack) + ".png",
        "data/textures/SkyboxBack" + std::to_string(skyboxTexPack) + ".png",
        "data/textures/SkyboxFront" + std::to_string(skyboxTexPack) + ".png"};
    this->skyboxTex = wolf::TextureManager::createCubemapTexture(paths);
    this->skyboxTex->SetCubemapFilterMode(wolf::Texture::FM_NearestMipmap);
}
Skybox::~Skybox()
{

    wolf::TextureManager::DestroyTexture(this->skyboxTex);
    this->skyboxTex = nullptr;
    delete m_pDecl;
    m_pDecl = nullptr;
    wolf::ProgramManager::DestroyProgram(m_pProgram);
    m_pProgram = nullptr;
    wolf::BufferManager::DestroyBuffer(m_pVB);
    m_pVB = nullptr;
}

void Skybox::render(const glm::mat4 &mProj, const glm::mat4 &mView)
{
    glm::mat4 view = glm::mat4(glm::mat3(mView));
    m_pProgram->SetUniform("projection_view", mProj * view);
    m_pProgram->SetUniform("skyboxTexture", 0);
    m_pProgram->Bind();
    m_pDecl->Bind();
    glDepthMask(GL_FALSE);
    this->skyboxTex->BindCubemapTex(0);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDepthMask(GL_TRUE);
}
