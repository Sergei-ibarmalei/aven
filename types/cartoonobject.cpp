#include "cartoonobject.h"

CartoonObject::CartoonObject(const Plot& center, const Texture* t,
                            const int nomberFrames)
{
    if (!t || nomberFrames <= 0)
    {
        init.Negate(); return;
    }
    allFrames = nomberFrames;
    textureMainRects = new Rect * [allFrames] {nullptr};
    objectMainRects  = new Rect * [allFrames] {nullptr};
    initRects(t, center);

}

void CartoonObject::initRects(const Texture* t, const Plot& center)
{
    for (auto frame = 0; frame < allFrames; frame++)
    {
        textureMainRects[frame] = new Rect {*t->operator[](frame)};
        objectMainRects[frame] = new Rect {
            center.x - ((t->operator[](frame)->w) >> 1),
            center.y - ((t->operator[](frame)->h) >> 1),
            t->operator[](frame)->w,
            t->operator[](frame)->h
        };
    }
}

CartoonObject::~CartoonObject()
{

    for (auto i = 0; i < allFrames; ++i)
    {
        delete textureMainRects[i];
        delete objectMainRects[i];
        objectMainRects[i] = nullptr;
        textureMainRects[i] = nullptr;
    }
    delete[] textureMainRects; textureMainRects = nullptr;
    delete[] objectMainRects;  objectMainRects  = nullptr;
}

void CartoonObject::Tick()
{
    this->currentFrame += 1;
    if (this->currentFrame > this->allFrames)
        this->objectStatus = enumObjectStatus::isCrashed;
}



