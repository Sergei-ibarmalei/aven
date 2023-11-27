#include "hero.h"


static Rect heroCollidingVector[HEROCOLLIDEVECTORLENGTH] =
{
    {184, 27, 4, 22},
    {174, 21, 4, 4},
    {149, 14, 4, 4},
    {124, 7, 4, 4},
    {105, 0, 4, 4},
    {90, 50, 4, 4},
    {83, 53, 4, 4},
    {77, 60, 4, 4}
};

Hero::Hero(const Texture* t, const Plot& start) :
    Ship(enumShipKind::hero, t, start, static_cast<int>(enumShipKind::hero))
{

    if (Ship::init_ok == false) return;
    fillCollide();
    heroStopIntro = MAINWINDOW_H >> 2;
}


bool Hero::crossedUp()
{
    return (this->objectMainRect->y + this->objectVelocity.y) <=
        awindow.y;
}

bool Hero::crossedDown()
{
    return (this->objectMainRect->y + this->objectMainRect->h +
        this->objectVelocity.y) >= awindow.y + awindow.h;
}

bool Hero::crossedRight()
{
    return (this->objectMainRect->x + this->objectMainRect->w +
        this->objectVelocity.x) >= awindow.x + awindow.w;
}


bool Hero::crossedLeft()
{
    return (this->objectMainRect->x + this->objectVelocity.x) <=
        awindow.x;
}

void Hero::fillCollide()
{
    for (auto r = 0; r < HEROCOLLIDEVECTORLENGTH; r++)
    {
        this->objectCollideVector[r] = new Rect{0, 0, 0, 0};
    }


}

void Hero::fillCollideAfterStart()
{
    for (auto r = 0; r < HEROCOLLIDEVECTORLENGTH; r++)
    {
        this->objectCollideVector[r]->x =
            this->objectMainRect->x + heroCollidingVector[r].x;
        this->objectCollideVector[r]->y =
            this->objectMainRect->y + heroCollidingVector[r].y;
        this->objectCollideVector[r]->w = heroCollidingVector[r].w;
        this->objectCollideVector[r]->h = heroCollidingVector[r].h;
    }


}

void Hero::Move()
{
    if (crossedUp())   return;
    if (crossedDown())  return;
    if (crossedLeft())  return;
    if (crossedRight()) return;
    Ship::recompute();

    //Перерасчет эшелона героя
    heroEshelon.ceiling = objectMainRect->y - HEROESHELONTOCEILING;
    heroEshelon.floor = objectMainRect->y + objectMainRect->h +
        HEROESHELONTOFLOOR;
}

void Hero::MoveIntro(GameState* gameState)
{
    if (gameState->heroIntro == false) return;
    this->objectMainRect->x += HEROINTRO_VEL;
    recomputeIntro();
    if (this->objectMainRect->x >= this->heroStopIntro)
    {
        gameState->heroIntro = false;
        this->objectVelocity.x = 0;
        fillCollideAfterStart();
        laserStartPos = Ship::setLaserStartPos(enumShipKind::hero);
    }
}

void Hero::recomputeIntro()
{

    SimpleObject::recomputeObjectMainRect();

    if (this->objectStatus == enumObjectStatus::isOnScreen) return;

    if (*this->objectMainRect == awindow)
        this->objectStatus = enumObjectStatus::isOnScreen;
}


void Hero::MoveLeft(const int velocity_x)
{
    this->objectVelocity.x -= velocity_x;
    this->Move();
}

void Hero::MoveRight(const int velocity_x)
{
    this->objectVelocity.x += velocity_x;
    this->Move();
}

void Hero::MoveUp(const int velocity_y)
{
    this->objectVelocity.y -= velocity_y;
    this->Move();
}

void Hero::MoveDown(const int velocity_y)
{
    this->objectVelocity.y += velocity_y;
    this->Move();
}

void Hero::Stop()
{
    this->objectVelocity.x = this->objectVelocity.y = 0;
}

bool Hero::operator==(const Ship& ship)
{
    return *Ship::objectMainRect == *ship.GetShipMainRect();
}


