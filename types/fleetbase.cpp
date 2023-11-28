#include "fleetbase.h"

FleetBase::FleetBase(const int size)
{
    if (size <= 0)
    {
        init.Negate(); return;
    }
    fleetVectorLength = size;
    currentFleetSize = size;

}


FleetBase::~FleetBase()
{
    /*for (auto& ship : fleetVector)
    {
        delete ship;
        ship = nullptr;
    }*/
    /*for (auto ship = 0; ship < fleetVectorLength; ++ship)
    {
        delete fleetVector[ship];
        fleetVector[ship] = nullptr;
    }
    delete[] fleetVector;
    fleetVector = nullptr;*/
    deleting();

}

Ship* FleetBase::operator[](const int index)
{
    if (index < 0) return fleetVector[0];
    if (index >= fleetVectorLength) return fleetVector[fleetVectorLength-1];
    return fleetVector[index];
}

void FleetBase::deleting()
{
    for (auto ship = 0; ship < fleetVectorLength; ++ship)
    {
        delete fleetVector[ship];
        fleetVector[ship] = nullptr;
    }
    delete[] fleetVector;
    fleetVector = nullptr;
}
