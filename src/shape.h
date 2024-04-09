#pragma once
#include "../wolf/wolf.h"

class Shape
{
public:
    //--------------------------------------------------------------------------------
    //
    // PUBLIC METHODS
    //
    //--------------------------------------------------------------------------------
    ~Shape(){};

    virtual glm::vec2 getMinMaxX() = 0;

    virtual glm::vec2 getMinMaxY() = 0;

    virtual glm::vec2 getMinMaxZ() = 0;

    virtual std::string getShapeType() = 0;

protected:
    //--------------------------------------------------------------------------------
    //
    // PRIVATE METHODS
    //
    //--------------------------------------------------------------------------------
    Shape(){};
};