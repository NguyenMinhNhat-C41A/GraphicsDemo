#include "sampleMultiTex.h"
#include "../samplefw/Grid2D.h"
#include "../wolf/stb_image.h"

struct Vertex
{
    GLfloat x, y;
    GLfloat u, v;
};

static const Vertex gs_squareVertices[] = {
    {100.0f, 100.0f, 0, 1},
    {100.0f, 300.0f, 0, 0},
    {300.0f, 300.0f, 1, 0},

    {300.0f, 300.0f, 1, 0},
    {300.0f, 100.0f, 1, 1},
    {100.0f, 100.0, 0, 1},
};

SampleMultiTex::~SampleMultiTex()
{
    printf("Destroying Multi Texture Sample\n");
    delete m_pDecl;
    wolf::ProgramManager::DestroyProgram(m_pProgram);
    wolf::BufferManager::DestroyBuffer(m_pVB);
    wolf::TextureManager::DestroyTexture(m_pTex1);
    wolf::TextureManager::DestroyTexture(m_pTex2);
}

void SampleMultiTex::init()
{
    // Only init if not already done
    if (!m_pProgram)
    {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        m_pProgram = wolf::ProgramManager::CreateProgram("data/two_textures.vsh", "data/two_textures.fsh");
        m_pVB = wolf::BufferManager::CreateVertexBuffer(gs_squareVertices, sizeof(Vertex) * 6);

        m_pDecl = new wolf::VertexDeclaration();
        m_pDecl->Begin();
        m_pDecl->AppendAttribute(wolf::AT_Position, 2, wolf::CT_Float);
        m_pDecl->AppendAttribute(wolf::AT_TexCoord1, 2, wolf::CT_Float);
        m_pDecl->SetVertexBuffer(m_pVB);
        m_pDecl->End();

        m_pTex1 = wolf::TextureManager::CreateTexture("data/brick.tga");
        m_pTex2 = wolf::TextureManager::CreateTexture("data/lmap.tga");
    }

    printf("Successfully initialized Multi Texture Sample\n");
}

void SampleMultiTex::update(float dt)
{
    m_fTime += dt;
}

void SampleMultiTex::render(int width, int height)
{
    glClearColor(0.3f, 0.3f, 0.3f, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 mProj = glm::ortho(0.0f, (float)width, (float)height, 0.0f, 0.0f, 1000.0f);

    // Use shader program.
    m_pProgram->Bind();

    m_pTex1->Bind(0);
    m_pTex2->Bind(1);

    // Bind Uniforms
    m_pProgram->SetUniform("projection", mProj);
    m_pProgram->SetUniform("texture1", 0);
    m_pProgram->SetUniform("texture2", 1);

    m_pProgram->SetUniform("time", m_fTime);

    // Set up source data
    m_pDecl->Bind();

    // Draw!
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
