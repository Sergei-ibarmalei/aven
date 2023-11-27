#pragma once

#include "laser.h"


class FirstFleetAlienLaser: public Laser
{
    public:
    FirstFleetAlienLaser(const Texture* t, const Plot& start):
        Laser(enumLaserKind::alienLaser, t, start, 1) {}
    FirstFleetAlienLaser(const FirstFleetAlienLaser&) = delete;
    FirstFleetAlienLaser& operator=(const FirstFleetAlienLaser&) = delete;
};

