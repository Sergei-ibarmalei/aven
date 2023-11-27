#pragma once

#include "ship.h"
#include "enums/enumlaserkind.h"

class Laser : public SimpleObject
{
protected:
    enumLaserKind kind;
    Laser(enumLaserKind laserKind,
        const Texture* t,
        const Plot& start,
        const int objectMainRectNomber = 0);
public:

    virtual void Move();
    bool operator==(const ComplexObject& o);
    bool operator==(const Ship& ship);

    friend std::ostream& operator<<(std::ostream& os, const Laser& l);

};

