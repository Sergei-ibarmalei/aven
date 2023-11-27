#pragma once

struct HeroState
{
    bool hero_isAlive{ true };
    bool hero_isDead{ false };
};

struct GameState
{
    HeroState heroState;
    bool      gameOver;
    bool      heroIntro;
    bool      inGamePause;
    bool      inMainMenu;
    bool      inPartOne;
    bool      goingOut;
    bool      gamePause;
    bool      toSystem; //полный выход в систему
};

