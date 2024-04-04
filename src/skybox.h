#pragma once
#include <algorithm>
#include <iostream>
#include <vector>
#include "../wolf/wolf.h"
#include "../wolf/stb_image.h"

class Skybox
{
public:
    Skybox();
    ~Skybox();
    void render(const glm::mat4 &mProj, const glm::mat4 &mView);

private:
    wolf::Texture *skyboxTex;
};