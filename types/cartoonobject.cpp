#include "cartoonobject.h"

CartoonObject::CartoonObject(const Plot& center, const Texture* t,
                            const int nomberFrames)
{
    if (!t || nomberFrames <= 0)
    {
        init_ok = false; return;
    }
    this->allFrames = nomberFrames;
    initRects(t, center);

}

void CartoonObject::initRects(const Texture* t, const Plot& center)
{
    for (auto frame = 0; frame < allFrames; frame++)
    {
        this->textureMainRects.push_back(t->operator[](frame));
        this->objectMainRects.push_back(new Rect{
            center.x - ((t->operator[](frame)->w)>>1),
            center.y - ((t->operator[](frame)->h)>>1),
            t->operator[](frame)->w,
            t->operator[](frame)->h });
    }
}

CartoonObject::~CartoonObject()
{
    for (SDL_Rect* r : textureMainRects)
    {
        delete r;
        r = nullptr;
    }
    for (SDL_Rect* r : objectMainRects)
    {
        delete r;
        r = nullptr;
    }
}

void CartoonObject::Tick()
{
    this->currentFrame += 1;
    if (this->currentFrame > this->allFrames)
        this->objectStatus = enumObjectStatus::isCrashed;
}



