#pragma once

#include <random>
#include "rect.h"
#include "../const/skyconst.h"

class Sky
{
private:

    Plot sky[13] = {
        {289,502},
        {252,939},
        {61,234},
        {682,743},
        {814,981},
        {1200,225},
        {1038,667},
        {1182,909},
        {1313,583},
        {1328,330},
        {1827,500},
        {1807,819}
    };
    Plot fast[FASTSTARARRLENGTH] = {
        {481, 627},
        {1030, 527},
        {1599,819}
    };
    Plot slow[SLOWSTARARRLENGTH] = {
        {239,716},
        {370,479},
        {945,720},
        {1566,551},
        {1888,505}
    };
    int ceiling{ 429 };
    int floor{ 976 };
    void moving(std::mt19937& mt, Plot* array, const int l, const int vel);

public:
    Sky() {}
    Sky(const Sky&) = delete;
    Sky& operator=(const Sky&) = delete;
    const Plot* StaticSky() const { return sky; }
    const Plot* FastStars() const { return fast; }
    const Plot* SlowSky()   const { return slow; }
    void Move(std::mt19937& mt);
};

