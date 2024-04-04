#include "sampleTextureFromFile.h"
#include "../samplefw/Grid2D.h"
#include "../wolf/stb_image.h"

struct Vertex
{
	GLfloat x,y;
	GLfloat u,v;
};

static const Vertex gs_squareVertices[] = {
	{ 100.0f, 100.0f,	0, 1 }, 
	{ 100.0f, 300.0f,	0, 0 }, 
	{ 300.0f, 300.0f,	1, 0 }, 

	{ 300.0f, 300.0f,	1, 0 }, 
	{ 300.0f, 100.0f,	1, 1 }, 
	{ 100.0f, 100.0,	0, 1 }, 
};

SampleTextureFromFile::~SampleTextureFromFile()
{
	printf("Destroying Texture From File Sample\n");
	delete m_pDecl;
	wolf::ProgramManager::DestroyProgram(m_pProgram);
	wolf::BufferManager::DestroyBuffer(m_pVB);
    glDeleteTextures(1, &m_tex);
}

void SampleTextureFromFile::init()
{
    // Only init if not already done
    if(!m_pProgram)
    {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        m_pProgram = wolf::ProgramManager::CreateProgram("data/one_texture.vsh", "data/one_texture.fsh");
        m_pVB = wolf::BufferManager::CreateVertexBuffer(gs_squareVertices, sizeof(Vertex) * 6);

        m_pDecl = new wolf::VertexDeclaration();
        m_pDecl->Begin();
        m_pDecl->AppendAttribute(wolf::AT_Position, 2, wolf::CT_Float);
        m_pDecl->AppendAttribute(wolf::AT_TexCoord1, 2, wolf::CT_Float);
        m_pDecl->SetVertexBuffer(m_pVB);
        m_pDecl->End();

        glGenTextures(1, &m_tex);
		printf("tex was %d\n", m_tex);
        glBindTexture(GL_TEXTURE_2D, m_tex);

        int w, h, n;
        unsigned char *pData = stbi_load("data/brick.tga", &w, &h, &n, 0);
        int format = -1;
        switch (n)
        {
        case 1:
            format = GL_R;
            break;
        case 2:
            format = GL_RG;
            break;
        case 3:
            format = GL_RGB;
            break;
        case 4:
            format = GL_RGBA;
            break;
        default:
            printf("Error: unknown image format %d\n", n);
            return;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, pData);
        stbi_image_free(pData);

        // These two lines are explained soon!
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }

    printf("Successfully initialized Texture From File Sample\n");
}

void SampleTextureFromFile::update(float dt) 
{
}

void SampleTextureFromFile::render(int width, int height)
{
	glClearColor(0.3f, 0.3f, 0.3f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 mProj = glm::ortho(0.0f,(float)width,(float)height,0.0f,0.0f,1000.0f);

    // Use shader program.
	m_pProgram->Bind();
    
	glActiveTexture(GL_TEXTURE0); // explained soon
	glBindTexture(GL_TEXTURE_2D, m_tex);
    
	// Bind Uniforms
    m_pProgram->SetUniform("projection", mProj);
    m_pProgram->SetUniform("tex", 0);
    
	// Set up source data
	m_pDecl->Bind();

    // Draw!
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

