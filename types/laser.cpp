#include "laser.h"

Laser::Laser(enumLaserKind laserKind,
    const Texture* t,
    const Plot& start,
    const int objectMainRectNomber) :
    SimpleObject(t, start, objectMainRectNomber)
{
    this->kind = laserKind;
    switch (laserKind)
    {
        case enumLaserKind::heroLaser:
        {
            this->objectVelocity.x = HEROLASER_VEL;
            break;
        }
        case enumLaserKind::alienLaser:
        {
            this->objectVelocity.x = ALIENLASER_VEL;
            break;
        }
        default: {}
    }
}

void Laser::Move()
{
    if (this->ObjectStatus() != enumObjectStatus::isOnScreen) return;

    switch (kind)
    {
        case enumLaserKind::heroLaser:
        {
            this->objectMainRect->x += this->objectVelocity.x;
            break;
        }
        case enumLaserKind::alienLaser:
        {
            this->objectMainRect->x -= this->objectVelocity.x;
            break;
        }
        default: {}
    }
    if (*this->objectMainRect == awindow) this->objectStatus =
        enumObjectStatus::isOnScreen;
    else this->objectStatus = enumObjectStatus::isCrashed;

}

bool Laser::operator==(const ComplexObject& o)
{
    int lengthCollideVector = o.CmplObjectCollideVectorLength();
    Rect** objectCollideVector = o.ObjectCollideVector();
    if (*this->objectMainRect == *o.ObjectMainRect())
    {
        for (auto r = 0; r < lengthCollideVector; r++)
        {

            if (*this->objectMainRect == *objectCollideVector[r]) return true;
        }
    }
    return false;
}

bool Laser::operator==(const Ship& o)
{
    int lengthCollideVector = o.CmplObjectCollideVectorLength();
    Rect** objectCollideVector = o.ObjectCollideVector();
    if (*this->objectMainRect == *o.ObjectMainRect())
    {
        for (auto r = 0; r < lengthCollideVector; r++)
        {

            if (*this->objectMainRect == *objectCollideVector[r]) return true;
        }
    }
    return false;
}

std::ostream& operator<<(std::ostream& os, const Laser& l)
{
    os << "new laser at: [" << l.startPos.x << ", " << l.startPos.y <<
        "]\n";
    return os;
}



