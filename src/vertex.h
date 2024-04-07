#pragma once
#include "../wolf/wolf.h"
struct CubeVertex
{
    GLfloat x, y, z;
};

struct QuadVertex
{
    GLfloat x, y, z;
};

struct QuadVertexColoured
{
    GLfloat x, y, z, r, g, b, a;
};

struct QuadVertexTextured
{
    GLfloat x, y, z, u, v;
};
