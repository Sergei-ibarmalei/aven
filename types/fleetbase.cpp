#include "fleetbase.h"

FleetBase::FleetBase(const int size)
{
    if (size <= 0)
    {
        init_ok = false; return;
    }
    this->currentFleetSize = size;

}


FleetBase::~FleetBase()
{
    for (auto& ship : fleetVector)
    {
        delete ship;
        ship = nullptr;
    }

}
