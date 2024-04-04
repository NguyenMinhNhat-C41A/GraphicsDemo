#pragma once
#include <iostream>
#include <vector>
#include "../thirdparty/tinyxml2/tinyxml2.h"
#include "factoryMethodsManager.h"
#include "node.h"
#include "vertex.h"
#include "boundingSphere.h"
class DebugCube : public Node
{
public:
    static Node *Factory(tinyxml2::XMLNode *p_pXMLNode);
    DebugCube(std::string p_newName, const glm::vec3 &p_vNewSc, const glm::vec3 &p_vNewRo, const glm::vec3 &p_vNewTr);
    ~DebugCube();

    virtual void update(float p_dt);
    virtual void render(const glm::mat4 &p_mProj, const glm::mat4 &p_mView) override;
    virtual void renderWithBounds(const glm::mat4 &p_mProj, const glm::mat4 &p_mView) override;
    virtual float calculateCentreToFurthestPoint() override;

private:
    static wolf::VertexBuffer *s_pVB;
    static wolf::VertexDeclaration *s_pDecl;
    static wolf::Program *s_pProgram;

    static int cubeCounter;
};
