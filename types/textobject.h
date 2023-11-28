#pragma once

#include "simpleobject.h"

class TextObject : public SimpleObject
{
private:
    Init init;
public:
    TextObject(const Texture* t, const Plot& start, 
        const int objectMainRectNomber = 0);

    const Plot& GetCenter() = delete;
    void NowIsCrashed() = delete;
    bool Init_ok() const {return init.Init_ok();}
};

