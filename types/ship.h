#pragma once

#include "complexobject.h"
#include "scorebase.h"
#include "../const/collidevectors.h"
#include "../const/laserconst.h"


class Ship : public ComplexObject, public ScoreBase
{
private:
    Init init;

protected:
    Plot* laserStartPos = nullptr;
    Plot* setLaserStartPos(enumShipKind kind);
    void   initCollideVector(enumShipKind shipKind);
    void  recompute();


public:
    Ship(enumShipKind shipKind,
        const Texture* t,
        const Plot& start,
        const int objectMainRectNomber = 0,
        const int objectScore = 0);
    Ship(const Ship&) = delete;
    Ship& operator=(const Ship&) = delete;
    ~Ship();
    virtual void Move() {}
    Plot* GetLaserStart()  const { return laserStartPos; }
    Rect* GetShipMainRect() const {return objectMainRect;}

    bool InEshelon(const Eshelon& e);
    bool Init_ok() const {return init.Init_ok();}
};