#pragma once


#include "texture.h"
#include "enums/enumhudlives.h"
#include "enums/enumhudlivesposition.h"

class HUD_lives
{
private:
    Init init;
    const Plot live_half{ 46, 50 };
    const Plot dead_half{ 45, 49 };

    int heroLives{ 3 };
    Plot centers[3]{};


    Rect lives_three[static_cast<int>(enumHudLivesPosition::all)]{};
    Rect lives_two[static_cast<int>(enumHudLivesPosition::all)]{};
    Rect lives_one[static_cast<int>(enumHudLivesPosition::all)]{};
    Rect lives_zero[static_cast<int>(enumHudLivesPosition::all)]{};

    void setLivesThree(const Plot* centers, const Texture* t);
    void setLivesTwo(const Plot* centers, const Texture* t);
    void setLivesOne(const Plot* centers, const Texture* t);
    void setLivesZero(const Plot* centers, const Texture* t);

    void setCenters();


public:
    explicit HUD_lives(const Texture* t);
    HUD_lives(const HUD_lives&) = delete;
    HUD_lives& operator=(const HUD_lives&) = delete;

    const Rect* Lives_three() const { return lives_three; }
    const Rect* Lives_two()   const { return lives_two; }
    const Rect* Lives_one()   const { return lives_one; }
    const Rect* Lives_zero()  const { return lives_zero; }

    int GetHeroLives() const { return heroLives; }
    void DecHeroLives() { heroLives -= 1; }
    void Reinit();
    bool Init_ok() const {return init.Init_ok();}

};