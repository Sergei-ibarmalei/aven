#include "fleetalienone.h"

Fleet_AlienOne::Fleet_AlienOne(std::mt19937& mt,
    const TextureStore* store,
    enumFleetKind kind,
    const int size): FleetBase(size)
{
    switch (kind)
    {
        case enumFleetKind::alienOneFleet:
        {
            init.Set(
                makeFleetOne(mt, store->operator[](enumTextureType::ships)));
            break;
        }
        default: {}
    }
}


bool Fleet_AlienOne::makeFleetOne(std::mt19937& mt, const Texture* t)
{
    int startPoint{ MAINWINDOW_W };
    int step{ 550 };
    int sideShift{ 100 };
    int alienHeight{ ALIENONE_MAINRECTH };
    int ceiling{ awindow.y + sideShift };
    int floor{ awindow.h - sideShift - alienHeight };
    Plot start{ 0, 0 };

    std::uniform_int_distribution<int> y{ ceiling, floor };
    fleetVector = new Ship * [fleetVectorLength] {nullptr};
    for (auto fleetShip = 0; fleetShip < this->currentFleetSize; ++fleetShip)
    {
        start.x = startPoint + step * fleetShip;
        start.y = y(mt);
        //auto ship = new Alien_one(t, start, ALIENONE_SCORE);
        //if (ship->Init_ok() == false) return false;
        //this->fleetVector.push_back(ship);
        fleetVector[fleetShip] = new Alien_one{t, start, ALIENONE_SCORE};
        if (fleetVector[fleetShip]->Init_ok() == false)
        {
            init.Negate(); return false;
        }
    }
    return true;
}

