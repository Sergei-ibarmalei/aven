#include "alienone.h"


Alien_one::Alien_one(const Texture* t,
                     const Plot& start,
                     const int objectScore) :
    Ship(enumShipKind::alien_one,
                       t,
                       start,
                       static_cast<int>(enumShipKind::alien_one),
                       objectScore)
{
    if (Ship::init_ok == false) return;
    fillCollide();
    this->objectVelocity.x = ALIENONEFLEET_VEL;
    alienShooting = new AlienStrightShooting {ALIENONE_STEPTOSHOOT};
}

void Alien_one::fillCollide()
{
    for (auto r = 0; r < ALIENONECOLLIDEVECTORLENGTH; r++)
    {
        this->objectCollideVector[r] =
            new Rect{ this->objectMainRect->x + alienCollidingVector[r].x,
                     this->objectMainRect->y + alienCollidingVector[r].y,
                     alienCollidingVector[r].w,
                     alienCollidingVector[r].h };
    }

}


void Alien_one::Move()
{
    if (this->ObjectStatus() == enumObjectStatus::isCrashed) return;

    Ship::recompute();

    //отсчитываем шаги для выполнения выстрела
    this->alienShooting->CountStepToShoot(this->ObjectStatus(),
        this->objectVelocity.x);

    if (this->objectStatus == enumObjectStatus::isOnScreen &&
        !(*this->objectMainRect == awindow))
    {
        this->objectStatus = enumObjectStatus::isCrashed;
        return;
    }

}

Alien_one::~Alien_one()
{
    delete alienShooting;
    alienShooting = nullptr;
}
