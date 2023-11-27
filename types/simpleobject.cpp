#include "simpleobject.h"

SimpleObject::SimpleObject(const Texture* t,
    const Plot& start,
    const int objectMainRectNomber)
{
    if (!t)
    {
        init_ok = false; return;
    }
    this->objectMainRect = new Rect{ 0, 0, 0, 0 };
    this->startPos = start;
    if (!setMainRectFromTexture(t->operator[](objectMainRectNomber)))
    {
        init_ok = false; return;
    }
    initObjectMainRect();
}

bool SimpleObject::setMainRectFromTexture(Rect* mainRectFromTexture_)
{
    if (!mainRectFromTexture_) return false;
    this->mainRectFromTexture = mainRectFromTexture_;
    return true;
}

SimpleObject::~SimpleObject()
{
    mainRectFromTexture = nullptr;
    delete objectMainRect;
    objectMainRect = nullptr;

}



void SimpleObject::initObjectMainRect()
{
    this->objectMainRect->x = startPos.x;
    this->objectMainRect->y = startPos.y;
    this->objectMainRect->w = this->mainRectFromTexture->w;
    this->objectMainRect->h = this->mainRectFromTexture->h;
    if (*this->objectMainRect == awindow)
        this->objectStatus = enumObjectStatus::isOnScreen;

    //init Center
    this->objectCenter.x = this->objectMainRect->x +
        (this->mainRectFromTexture->w >> 1);
    this->objectCenter.y = this->objectMainRect->y +
        (this->mainRectFromTexture->h >> 1);
}

void SimpleObject::recomputeObjectMainRect()
{
    if (this->objectMainRect)
    {
        this->objectMainRect->x += this->objectVelocity.x;
        this->objectMainRect->y += this->objectVelocity.y;

        this->objectCenter.x = this->objectMainRect->x + 
            (this->objectMainRect->w >> 1);
        this->objectCenter.y = this->objectMainRect->y +
            (this->objectMainRect->h >> 1);


    }

}

std::ostream& operator<<(std::ostream& os, const SimpleObject& o)
{
    os << "Object main rect: [x: " << o.objectMainRect->x <<
        ", y: " << o.objectMainRect->y <<
        ", w: " << o.objectMainRect->w <<
        ", h: " << o.objectMainRect->h << "]\n" <<
        "Object texture main rect: [x: " << o.mainRectFromTexture->x <<
        ", y: " << o.mainRectFromTexture->y <<
        ", w: " << o.mainRectFromTexture->w <<
        ", h: " << o.mainRectFromTexture->h << "]\n";
    return os;
}

bool SimpleObject::InEshelon(const Eshelon& e)
{
    return (objectCenter.y > e.ceiling && objectCenter.y < e.floor);
}


