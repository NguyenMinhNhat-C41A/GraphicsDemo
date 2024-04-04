#pragma once
#include "../wolf/wolf.h"
#include "../samplefw/Sample.h"

class SampleMultiTex: public Sample
{
public:
    SampleMultiTex(wolf::App* pApp) : Sample(pApp,"Multi Texturing") {}
    ~SampleMultiTex();

    void init() override;
    void update(float dt) override;
    void render(int width, int height) override;

private:
    wolf::VertexBuffer* m_pVB = 0;
    wolf::VertexDeclaration* m_pDecl = 0;
    wolf::Program* m_pProgram = 0;
    wolf::Texture* m_pTex1;
    wolf::Texture* m_pTex2;
    float m_fTime = 0;
};
