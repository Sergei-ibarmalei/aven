#pragma once

#include "laser.h"

class HeroLaser : public Laser
{
private:

public:
    HeroLaser(const Texture* t, const Plot& start):
        Laser(enumLaserKind::heroLaser, t, start) {}
    HeroLaser(const HeroLaser&) = delete;
    HeroLaser& operator=(const HeroLaser&) = delete;
};