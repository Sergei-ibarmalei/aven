#pragma once

#include "cartoonobject.h"
#include "texturestore.h"


constexpr int BLOW_FRAMES {7};

class CartoonBlow : public CartoonObject
{
public:
    CartoonBlow(const TextureStore* store, const Plot& center) :
        CartoonObject(center, store->operator[](enumTextureType::cartoonBlow),
                        BLOW_FRAMES) {}
};

