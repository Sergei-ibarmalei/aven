#pragma once

#include "ship.h"
#include "states.h"
#include "../const/velconst.h"


class Hero : public Ship
{
private:
    int heroStopIntro;
    bool crossedUp();
    bool crossedDown();
    bool crossedRight();
    bool crossedLeft();
    Eshelon heroEshelon{0, 0};

    void fillCollide() override;
    void fillCollideAfterStart();

    void recomputeIntro(); //�������� ��������� ��� Intro


public:
    Hero(const Texture* t, const Plot& start);
    Hero(const Hero&) = delete;
    Hero& operator=(const Hero&) = delete;


    void MoveRight(const int velocity_x);
    void MoveLeft(const int velocity_x);
    void MoveUp(const int velocity_y);
    void MoveDown(const int velocity_y);
    void Stop();
    void Move();
    void MoveIntro(GameState* gameState);
    const Eshelon& GetHeroEshelon() const {return heroEshelon;}
    bool operator==(const Ship& ship);
};