#pragma once

enum class enumTextureType {
    ships,
    gameFon,
    digitsPack,
    shlemsPack,
    lasersPack,
    cartoonBlow,
    mainmenuText,
    fontPause,    // надпись PAUSE
    fontPressQ,   // ... Press Q to continue, Esc to exit
    fontPressEsc, // ... Press Esc to exit
    fontDE,       // ... DE
    fontAD,       // ... AD
    fontGameover, // ... GAME OVER
    all
};

enum class enumCartoonBloowFrames
{
    first,
    second,
    third,
    fourth,
    fifth,
    sixth,
    seventh,
    all
};

enum class enumLasers {
    blue,
    red,
    yellow,
    all
};

enum class enumLaserKind {
    heroLaser,
    alienLaser,
    all
};

enum class enumHudLivesPosition {
    left,
    center,
    right,
    all
};

enum class enumHudLives
{
    zero,
    one,
    two,
    three,
    all
};

enum class enumHudScoreDigits {
    zero,
    one,
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
    nine,
    all
};

enum class enumObjectStatus
{
    isReady,
    isOnScreen,
    isCrashed,
};

enum class enumFon {
    gameFon,
    all
};

enum class enumDigitsPack {
    zero,
    one,
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
    nine,
    all
};

enum class enumShlemsPack {
    liveShlem,
    deadShlem,
    all
};

enum class enumShipKind {
    hero,
    alien_one,
    alien_two,
    alien_silent_blue,
    alien_silent_brown,
    all
};

enum class enumFleetKind
{
    alienOneFleet,
    all
};

enum class enumHeroCollides {
    one,
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
    all
};
enum class enumAlienOneCollides {
    one,
    two,
    three,
    four,
    five,
    six,
    seven,
    all,
};

enum class enumTextingOrder {
    black_newgame,
    black_rules,
    black_exit,
    red_newgame,
    red_rules,
    red_exit,
    all
};

enum class enumMainMenuChoise {
    new_game,
    rules,
    exit,
    all
};

enum class enumGameFonts
{
    pause,
    pressQ,
    pressEsc,
    de,
    ad,
    gameover,
    all
};





