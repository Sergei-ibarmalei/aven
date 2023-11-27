#pragma once

#include <random>
#include "alienone.h"
#include "fleetbase.h"
#include "texturestore.h"
#include "enums/enumfleetfind.h"
#include "../const/scores.h"


class Fleet_AlienOne : public FleetBase
{
protected:
    bool makeFleetOne(std::mt19937& mt, const Texture* t);
public:

    Fleet_AlienOne(std::mt19937& mt,
        const TextureStore* store,
        enumFleetKind kind,
        const int fleetSize);
};

