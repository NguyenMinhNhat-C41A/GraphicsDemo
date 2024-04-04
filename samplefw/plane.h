#pragma once
#include <glm/glm.hpp>

struct Plane
{

    // glm::vec3 referencePoint = glm::vec3(0.0f);
    glm::vec3 normal = glm::vec3(1.0f);
    float distance = 0.0f;
    int tag = 0;
};
