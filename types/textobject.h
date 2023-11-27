#pragma once

#include "simpleobject.h"

class TextObject : public SimpleObject
{
public:
    TextObject(const Texture* t, const Plot& start, 
        const int objectMainRectNomber = 0) :
        SimpleObject(t, start, objectMainRectNomber) {}

    const Plot& GetCenter() = delete;
    void NowIsCrashed() = delete;
};

