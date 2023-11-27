#pragma once

#include <SDL2/SDL.h>
#include <iostream>


struct Rect : public SDL_Rect
{
    Rect(const int x = 0,
        const int y = 0,
        const int w = 0,
        const int h = 0) : SDL_Rect{ x, y, w, h } {}

    bool operator==(const Rect& r) const
    {
        if ((y + h) <= r.y)  return false;
        if (y >= (r.y + r.h)) return false;
        if ((x + w) <= r.x)  return false;
        if (x >= (r.x + r.w))  return false;
        return true;
    }



    friend std::ostream& operator<<(std::ostream& os, const Rect&);
};

struct Plot
{
    int x, y;
};

