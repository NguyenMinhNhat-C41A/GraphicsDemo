#pragma once
#include "../wolf/wolf.h"
#include "../samplefw/Sample.h"

class SampleSimpleTexture: public Sample
{
public:
    SampleSimpleTexture(wolf::App* pApp) : Sample(pApp,"Simple Texture") {}
    ~SampleSimpleTexture();

    void init() override;
    void update(float dt) override;
    void render(int width, int height) override;

private:
    wolf::VertexBuffer* m_pVB = 0;
    wolf::VertexDeclaration* m_pDecl = 0;
    wolf::Program* m_pProgram = 0;
    GLuint m_tex = 0;
};