#pragma once
#include "../wolf/wolf.h"
#include "../samplefw/Sample.h"

class SampleTextureFromFile: public Sample
{
public:
    SampleTextureFromFile(wolf::App* pApp) : Sample(pApp,"Texture From File") {}
    ~SampleTextureFromFile();

    void init() override;
    void update(float dt) override;
    void render(int width, int height) override;

private:
    wolf::VertexBuffer* m_pVB = 0;
    wolf::VertexDeclaration* m_pDecl = 0;
    wolf::Program* m_pProgram = 0;
    GLuint m_tex = 0;
};
