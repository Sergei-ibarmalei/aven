#include "sky.h"

void Sky::moving(std::mt19937& mt, Plot* arr, const int length, const int vel)
{
    for (auto s = 0; s < length; s++)
    {
        arr[s].x -= vel;
        if (arr[s].x < awindow.x)
        {
            arr[s].x = awindow.w;
            std::uniform_int_distribution<int> y{ ceiling, floor };
            arr[s].y = y(mt);
        }
    }
}

void Sky::Move(std::mt19937& mt)
{
    moving(mt, fast, FASTSTARARRLENGTH, FASTSTARVELOCITY);
    moving(mt, slow, SLOWSTARARRLENGTH, SLOWSTARVELOCITY);
}

