#include "alienstrightshooting.h"
#include <iostream>

void AlienStrightShooting::CountStepToShoot(enumObjectStatus status,
                                     const int velocity)
{
    if (mayShoot) return;
    if (status != enumObjectStatus::isOnScreen) return;
    currentStep -= velocity;  //velocity для алиена - число отрицательное
    if (currentStep >= stepsToShoot)
    {
        mayShoot = true;
    }
}

void AlienStrightShooting::CantShoot()
{
    mayShoot = false;
    currentStep = 0;
}

