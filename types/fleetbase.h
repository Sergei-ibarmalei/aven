#pragma once

#include <vector>
#include "ship.h"



class FleetBase : public Init
{
protected:
    std::vector<Ship*> fleetVector;
    int currentFleetSize{};
    bool fleetIsOver{ false };
    explicit FleetBase(const int size);
    FleetBase(const FleetBase&) = delete;
    FleetBase& operator=(const FleetBase&) = delete;
public:
    ~FleetBase();
    std::vector<Ship*>& GetFleet() { return fleetVector; }
    void DecCurrentFleetSize() {currentFleetSize -= 1;}
    int GetCurrentFleetSize() const { return currentFleetSize; }
    bool IsFleetOver() const { return fleetIsOver; }

};
