#include "sampleSimpleTexture.h"
#include "../samplefw/Grid2D.h"

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

static GLubyte gs_textureData[] = {
	0, 0, 255,	 // blue
	255, 255, 0, // yellow
	255, 0, 0,	 // red
	0, 255, 0,	 // green
};

SampleSimpleTexture::~SampleSimpleTexture()
{
	printf("Destroying Simple Texture Sample\n");
	delete m_pDecl;
	wolf::ProgramManager::DestroyProgram(m_pProgram);
	wolf::BufferManager::DestroyBuffer(m_pVB);
	glDeleteTextures(1, &m_tex);
}

void SampleSimpleTexture::init()
{
	// Only init if not already done
	if (!m_pProgram)
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
		glBindTexture(GL_TEXTURE_2D, m_tex);
		printf("tex was %d\n", m_tex);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_UNSIGNED_BYTE, gs_textureData);
		// These lines are explained soon!
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	printf("Successfully initialized Simple Texture Sample\n");
}

void SampleSimpleTexture::update(float dt)
{
}

void SampleSimpleTexture::render(int width, int height)
{
	glClearColor(0.3f, 0.3f, 0.3f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 mProj = glm::ortho(0.0f, (float)width, (float)height, 0.0f, 0.0f, 1000.0f);

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
