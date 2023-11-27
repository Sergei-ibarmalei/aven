#include "ship.h"


Ship::Ship(enumShipKind shipKind, const Texture* t,
    const Plot& start,
    const int objectMainRectNomber,
    const int objectScore) :
    ComplexObject(t, start, objectMainRectNomber), ScoreBase(objectScore)
{
    if (SimpleObject::init_ok == false) return;
    this->laserStartPos = setLaserStartPos(shipKind);
    initCollideVector(shipKind);

}

void Ship::initCollideVector(enumShipKind shipKind)
{
    switch (shipKind)
    {
        case enumShipKind::hero:
        {
            this->objectCollideVectorLength = HEROCOLLIDEVECTORLENGTH;
            this->objectCollideVector =
                new Rect * [this->objectCollideVectorLength];
            break;
        }
        case enumShipKind::alien_one:
        {
            this->objectCollideVectorLength = ALIENONECOLLIDEVECTORLENGTH;
            this->objectCollideVector =
                new Rect * [this->objectCollideVectorLength];
            break;
        }
        default: {}
    }
}

Plot* Ship::setLaserStartPos(enumShipKind shipKind)
{
    switch (shipKind)
    {
        case enumShipKind::hero:
        {
            return new Plot{ this->objectMainRect->x +
                this->objectMainRect->w + LASERSHIFT,
                this->objectMainRect->y + HEROLASER_YPOS };
            break;
        }
        case enumShipKind::alien_one:
        {
            return new Plot{ this->objectMainRect->x -
                LASERSHIFT - ALIENONELASER_W,
                this->objectMainRect->y + 
            ALIENONELASERGUN_Y - (ALIENONELASER_H>>1)  };
            break;
        }
        case enumShipKind::alien_two:
        {
            return new Plot{ this->objectMainRect->x -
                LASERSHIFT,
                this->objectMainRect->y +
            (this->objectMainRect->h >> 1) };
            break;
        }
        case enumShipKind::alien_silent_blue:
        case enumShipKind::alien_silent_brown:
        {
            return nullptr;
            break;
        }
        default: return nullptr;

    }
}


void Ship::recompute()
{
    if (this->objectStatus == enumObjectStatus::isCrashed) return;
    if (this->laserStartPos)
    {
        this->laserStartPos->x += this->objectVelocity.x;
        this->laserStartPos->y += this->objectVelocity.y;
    }
    ComplexObject::recomputeCollideVector();
    SimpleObject::recomputeObjectMainRect();

    if (this->objectStatus == enumObjectStatus::isOnScreen) return;

    if (*this->objectMainRect == awindow)
        this->objectStatus = enumObjectStatus::isOnScreen;

}

bool Ship::InEshelon(const Eshelon& e)
{
    return (this->objectCenter.y > e.ceiling && this->objectCenter.y < e.floor);
}

Ship::~Ship()
{
    if (this->laserStartPos)
    {
        delete this->laserStartPos;
        this->laserStartPos = nullptr;
    }
}

