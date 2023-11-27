#pragma once

#include "simpleobject.h"

class GameFon : public SimpleObject
{

public:
    explicit GameFon(const Texture* t) : SimpleObject(t, { 0, 0 })
    {
        initObjectMainRect();
    }
    GameFon(const GameFon&) = delete;
    GameFon& operator=(const GameFon&) = delete;
};

