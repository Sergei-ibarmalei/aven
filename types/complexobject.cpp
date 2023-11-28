#include "complexobject.h"


ComplexObject::ComplexObject(const Texture* t,
    const Plot& start,
    const int objectMainRectNomber) :
    SimpleObject(t, start, objectMainRectNomber)
{
    if (SimpleObject::Init_ok() == false) return;
}





void ComplexObject::recomputeCollideVector()
{
    if (!this->objectCollideVector) return;
    for (auto r = 0; r < this->objectCollideVectorLength; r++)
    {
        objectCollideVector[r]->x += this->objectVelocity.x;
        objectCollideVector[r]->y += this->objectVelocity.y;
    }
}

bool ComplexObject::operator==(const ComplexObject& o)
{
    if (!o.objectCollideVector || (o.objectCollideVectorLength <= 0))
        return false;

    if (*this->objectMainRect == *o.objectMainRect)
    {
        for (int r = 0; r < this->objectCollideVectorLength; r++)
        {
            for (int _or = 0; _or < o.objectCollideVectorLength; _or++)
            {
                if (*this->objectCollideVector[r] ==
                    *o.objectCollideVector[_or])
                    return true;
            }
        }
    }
    return false;
}

bool ComplexObject::operator==(const SimpleObject& s)
{
    if (!s.ObjectMainRect()) return false;
    return *this->objectMainRect == *s.ObjectMainRect();
}

ComplexObject::~ComplexObject()
{
    if (objectCollideVector && objectCollideVectorLength > 0)
    {
        for (auto r = 0; r < objectCollideVectorLength; r++)
        {
            delete objectCollideVector[r];
            objectCollideVector[r] = nullptr;
        }
        delete[] objectCollideVector;
        objectCollideVector = nullptr;
    }
}
