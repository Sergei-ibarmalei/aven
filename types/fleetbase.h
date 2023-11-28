#pragma once

#include "ship.h"



class FleetBase
{
protected:
    Init init;
    Ship** fleetVector {nullptr};
    int    fleetVectorLength {0};
    int currentFleetSize{};
    bool fleetIsOver{ false };
    explicit FleetBase(const int size);
    FleetBase(const FleetBase&) = delete;
    FleetBase& operator=(const FleetBase&) = delete;
public:
    ~FleetBase();
    void DecCurrentFleetSize() {currentFleetSize -= 1;}
    int GetCurrentFleetSize() const { return currentFleetSize; }
    int GetFleetVectorLength() const {return fleetVectorLength;}
    bool IsFleetOver() const { return fleetIsOver; }
    bool Init_ok() const {return init.Init_ok();}
    Ship* operator[](const int index);
    void deleting();
    

};
