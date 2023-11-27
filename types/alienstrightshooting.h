#pragma once

#include "enums/enumobjectstatus.h"

class AlienStrightShooting
{
private:
    int stepsToShoot = 0;
    int currentStep  = 0;
    bool mayShoot = false;
public:
    explicit AlienStrightShooting(const int StepsToShoot):
        stepsToShoot(StepsToShoot) {}
    void CountStepToShoot(enumObjectStatus status, const int velocity);
    bool MayShoot() const {return mayShoot;}
    void CantShoot();

};