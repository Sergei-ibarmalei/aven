#include "alienstrightshooting.h"

void AlienStrightShooting::CountStepToShoot(enumObjectStatus status,
                                     const int velocity)
{
    if (mayShoot) return;
    if (status != enumObjectStatus::isOnScreen) return;
    currentStep -= velocity;
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

