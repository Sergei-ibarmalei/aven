#pragma once

#include "ship.h"
#include "alienstrightshooting.h"
#include "../const/fleetsconst.h"

class Alien_one : public Ship
{
private:
    AlienStrightShooting* alienShooting = nullptr;
    void fillCollide() override;
public:
    Alien_one(const Texture* t, const Plot& start, const int objectScore);
    Alien_one(const Alien_one&) = delete;
    Alien_one& operator=(const Alien_one&) = delete;
    bool ThisAlienMayShoot() const {return alienShooting->MayShoot();}
    void ThisAlienCantShoot() {alienShooting->CantShoot();}
    ~Alien_one();

    void Move() override;

};

