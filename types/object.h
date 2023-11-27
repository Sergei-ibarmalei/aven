#pragma once

#include "rect.h"

class Object
{
protected:
    virtual bool setMainRectFromTexture(Rect* mainRectFromTexture) = 0;
    virtual void initObjectMainRect() = 0;
public:
    virtual ~Object() {}
};



