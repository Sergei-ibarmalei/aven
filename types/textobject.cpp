#include "textobject.h"

TextObject::TextObject(const Texture* t,
    const Plot& start,
    const int objectMainRectNomber):
    SimpleObject(t, start, objectMainRectNomber)
{
    if (SimpleObject::Init_ok() == false)
    {
        init.Negate(); return;
    }
}