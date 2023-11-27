#pragma once

#include <vector>
#include "texture.h"
#include "enums/enumobjectstatus.h"


class CartoonObject :public Init
{
protected:
    int currentFrame{ 1 };
    int allFrames{ 0 };
    enumObjectStatus objectStatus = enumObjectStatus::isOnScreen;
    std::vector<Rect*> textureMainRects{ nullptr };
    std::vector<Rect*> objectMainRects{ nullptr };
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
    const std::vector<Rect*>& SourceRects() { return textureMainRects; }
    const std::vector<Rect*>& DestRects() { return objectMainRects; }
    SDL_Rect* CurrentSourceRect() const 
        { return textureMainRects[this->currentFrame]; }
    SDL_Rect* CurrentDestRect() const 
        { return objectMainRects[this->currentFrame]; }
};
