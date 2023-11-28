#pragma once

#include "texture.h"
#include "enums/enumobjectstatus.h"


class CartoonObject
{
protected:
    Init init;
    int currentFrame{ 1 };
    int allFrames{ 0 };
    enumObjectStatus objectStatus = enumObjectStatus::isOnScreen;
    Rect** textureMainRects {nullptr};
    Rect** objectMainRects  {nullptr};
    void initRects(const Texture* t, const Plot& center);

    CartoonObject(const Plot& center,
        const Texture* t,
        const int nomberFrames);
    CartoonObject(const CartoonObject&) = delete;
    CartoonObject& operator=(const CartoonObject&) = delete;

public:

    ~CartoonObject();

    void Tick();
    enumObjectStatus ObjectStatus() const { return objectStatus; }
    SDL_Rect* CurrentSourceRect() const 
        { return textureMainRects[currentFrame-1]; }
    SDL_Rect* CurrentDestRect() const 
        { return objectMainRects[currentFrame-1]; }
    bool Init_ok() const {return init.Init_ok();}
};
