#pragma once

#include "cartoonobject.h"

struct CartoonNode
{
    CartoonObject* cartoonObject{ nullptr };
    struct CartoonNode* next{ nullptr };

    ~CartoonNode()
    {
        delete cartoonObject;
        cartoonObject = nullptr;
    }
};

