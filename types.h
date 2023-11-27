#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <math.h>
#include "inits.h"
#include "enums.h"
#include "texturesconst.h"
#include "laserconst.h"
#include "velconst.h"
#include "fleetsconst.h"
#include "scoreconst.h"
#include "skyconst.h"
#include "game_colors.hpp"
#include "test.h"
#include "templates.h"


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

struct Rect : public SDL_Rect
{
    Rect(const int x = 0,
        const int y = 0,
        const int w = 0,
        const int h = 0) : SDL_Rect{ x, y, w, h } {}

    bool operator==(const Rect& r) const
    {
        if ((y + h) <= r.y)  return false;
        if (y >= (r.y + r.h)) return false;
        if ((x + w) <= r.x)  return false;
        if (x >= (r.x + r.w))  return false;
        return true;
    }



    friend std::ostream& operator<<(std::ostream& os, const Rect&);
};

struct Eshelon
{
    int ceiling;
    int floor;
};

static const Rect awindow
{
    ACTIONWINDOW_SHIFT_X,
    ACTIONWINDOW_SHIFT_Y,
    MAINWINDOW_W - 2 * ACTIONWINDOW_SHIFT_X,
    MAINWINDOW_H - ACTIONWINDOW_SHIFT_X - ACTIONWINDOW_SHIFT_Y
};

class Texture : public Init
{
private:
    SDL_Texture* sdlTexture = nullptr;
    Rect** mainRectsVector = nullptr;
    int   mainRectsVectorLength = 0;
    void initMainRectsVector(enumTextureType textureType);
    void initMainRectsVectorFonts(SDL_Surface* surface);

public:
    Texture(SDL_Texture* t,
        Rect** rectsVector,
        const int rectsVectorLength,
        enumTextureType textureType);
    //Текстура из текста
    Texture(SDL_Texture* t,
        Rect** rectsVector,
        SDL_Surface* surface);
    ~Texture();
    Texture& operator=(const Texture&) = delete;
    Texture(const Texture&) = delete;
    Rect* operator[](const int index) const;
    SDL_Texture* GetTexture() const { return sdlTexture; }

};



class Sdl : public Init
{
private:
    SDL_Renderer* renderer = nullptr;
    SDL_Window* window = nullptr;
    SDL_Event      e{};
    TTF_Font** fontsArray = nullptr;
    int        fontsArrayLength {0};

    bool init(const char* appName, const int w, const int h);
    bool initFontsArray();

public:
    Sdl(const char* name);
    ~Sdl();
    Sdl(const Sdl&) = delete;
    Sdl& operator=(const Sdl&) = delete;
    SDL_Renderer* Render() const { return renderer; }
    SDL_Event& Event() { return e; }

    Texture* MakeTexture(const char* texturePath, enumTextureType textureType);
    Texture* MakeTexture(enumGameFonts gameFonts, const char* textToTexture);

};


struct Plot
{
    int x, y;
};



class Object
{
protected:
    virtual bool setMainRectFromTexture(Rect* mainRectFromTexture) = 0;
    virtual void initObjectMainRect() = 0;
public:
    virtual ~Object() {}
};





class SimpleObject : public Object, public Init
{
protected:
    enumObjectStatus  objectStatus = enumObjectStatus::isReady;
    Plot startPos{ 0, 0 };
    Plot objectCenter{ 0, 0 };
    Plot  objectVelocity{ 0, 0 };
    Rect* mainRectFromTexture = nullptr;
    Rect* objectMainRect = nullptr;
    void   recomputeObjectMainRect();
    bool setMainRectFromTexture(Rect* mainRectFromTexture) override;

    void initObjectMainRect() override;

public:
    SimpleObject(const Texture* t, /*������� �������*/
        const Plot& start, /* ��������� �����*/
        const int objectMainRectNomber = 0 /*���������� ����� main rect � ������� main rect ��������*/);
    SimpleObject(const SimpleObject&) = delete;
    SimpleObject& operator=(const SimpleObject&) = delete;
    ~SimpleObject();
    Rect* MainRectFromTexture() const { return mainRectFromTexture; }
    Rect* ObjectMainRect() const { return objectMainRect; }
    const Plot& GetCenter() const { return objectCenter; }
    enumObjectStatus ObjectStatus() const { return objectStatus; }
    void NowIsCrashed() { this->objectStatus = enumObjectStatus::isCrashed; }
    friend std::ostream& operator<<(std::ostream& os, const SimpleObject& o);
    bool InEshelon(const Eshelon& e);




};

class TextObject : public SimpleObject
{
public:
    TextObject(const Texture* t, const Plot& start, 
        const int objectMainRectNomber = 0) :
        SimpleObject(t, start, objectMainRectNomber) {}

    const Plot& GetCenter() = delete;
    void NowIsCrashed() = delete;
};





class ComplexObject : public SimpleObject
{
protected:
    Rect** objectCollideVector = nullptr;
    int    objectCollideVectorLength = 0;
    void   recomputeCollideVector();
    virtual void fillCollide() {}
    ComplexObject(const Texture* t,
        const Plot& start,
        const int objectMainRectNomber = 0);
    ComplexObject(const ComplexObject&) = delete;
    ComplexObject& operator=(const ComplexObject&) = delete;

public:
    ~ComplexObject();
    bool operator==(const ComplexObject& o);
    bool operator==(const SimpleObject& s);

    int CmplObjectCollideVectorLength() const
         { return objectCollideVectorLength; }
    Rect** ObjectCollideVector() const { return objectCollideVector; }

};







class ScoreBase
{
protected:
    int score{};
public:
    ScoreBase(const int objectScore);
    int GetScore() const { return score; }
};



class Ship : public ComplexObject, public ScoreBase
{
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
};

class Laser : public SimpleObject
{
protected:
    enumLaserKind kind;
    Laser(enumLaserKind laserKind,
        const Texture* t,
        const Plot& start,
        const int objectMainRectNomber = 0);
public:

    virtual void Move();
    bool operator==(const ComplexObject& o);
    bool operator==(const Ship& ship);

    friend std::ostream& operator<<(std::ostream& os, const Laser& l);

};



class HeroLaser : public Laser
{
private:

public:
    HeroLaser(const Texture* t, const Plot& start):
        Laser(enumLaserKind::heroLaser, t, start) {}
    HeroLaser(const HeroLaser&) = delete;
    HeroLaser& operator=(const HeroLaser&) = delete;
};

class FirstFleetAlienLaser: public Laser
{
    public:
    FirstFleetAlienLaser(const Texture* t, const Plot& start):
        Laser(enumLaserKind::alienLaser, t, start, 1) {}
    FirstFleetAlienLaser(const FirstFleetAlienLaser&) = delete;
    FirstFleetAlienLaser& operator=(const FirstFleetAlienLaser&) = delete;
};

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


class AlienStrightShooting
{
private:
    int stepsToShoot = 0;
    int currentStep  = 0;
    bool mayShoot = false;
public:
    explicit AlienStrightShooting(const int StepsToShoot):
        stepsToShoot(StepsToShoot) {}
    void CountStepToShoot(enumObjectStatus status, const int velocity);
    bool MayShoot() const {return mayShoot;}
    void CantShoot();

};


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





class TextureStore : public Init
{
private:
    const char* gameTexturesPaths[13] =  {
    "media/txt/ShipsGame.png",
    "media/txt/gameFon.png",
    "media/txt/digitsPack2.png",
    "media/txt/shlemsPack2.png",
    "media/txt/lasersPack.png",
    "media/txt/BoomPack.png",
    "media/txt/mainmenuPack.png",
    "PAUSE",
    "Press Q to exit, Esc to continue",
    "Press Esc to exit",
    "DE",
    "AD",
    "GAME OVER"
};
    Texture** store = nullptr;
    int       storeLength = 0;
    bool      fillStore(Sdl* sdl);
public:
    explicit TextureStore(Sdl* sdl);
    TextureStore(const TextureStore&) = delete;
    TextureStore& operator=(const TextureStore&) = delete;

    Texture* operator[](enumTextureType textureType) const;
    ~TextureStore();

};

class MainMenu : public Init
{
private:
    std::vector<SimpleObject*> mm_vector;
    std::vector<Plot> startPoints;
    int menuChoise{ 0 };
    void  initStartPoints(const Texture* t);
    void initVector(const Texture* t);
public:
    explicit MainMenu(const Texture* t);
    void NextChoise();
    void PrevChoise();
    const std::vector<SimpleObject*>& GetMainMenu() const { return mm_vector; }
    int GetChoise() const { return menuChoise; }
    ~MainMenu();
};

class GameFon : public SimpleObject
{

public:
    explicit GameFon(const Texture* t) : SimpleObject(t, { 0, 0 })
    {
        initObjectMainRect();
    }
    GameFon(const GameFon&) = delete;
    GameFon& operator=(const GameFon&) = delete;
};


class HUD_lives : public Init
{
private:
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

};

constexpr int HUD_SCORE_LENGTH{ 5 };

class HUD_score
{
private:
    int gameScore{};
    const Plot HUD_SCORE_CENTER{ 1685, 61 };
    const int delimeter[HUD_SCORE_LENGTH]{ 10'000, 1000, 100, 10, 1 };
    Rect  hudScoreMainRects[HUD_SCORE_LENGTH];
    int   hudScore[HUD_SCORE_LENGTH]{};


    void initHudScoreMainRects();

public:
    HUD_score();
    HUD_score(const HUD_score&) = delete;
    HUD_score& operator=(const HUD_score&) = delete;
    void SetScore(int score);
    const Rect* HudScoreMainRects()    const { return hudScoreMainRects; }
    const int* HudScore() const { return hudScore; }
    void ResetGameScore();

};



class Sky
{
private:

    Plot sky[13] = {
        {289,502},
        {252,939},
        {61,234},
        {682,743},
        {814,981},
        {1200,225},
        {1038,667},
        {1182,909},
        {1313,583},
        {1328,330},
        {1827,500},
        {1807,819}
    };
    Plot fast[FASTSTARARRLENGTH] = {
        {481, 627},
        {1030, 527},
        {1599,819}
    };
    Plot slow[SLOWSTARARRLENGTH] = {
        {239,716},
        {370,479},
        {945,720},
        {1566,551},
        {1888,505}
    };
    int ceiling{ 429 };
    int floor{ 976 };
    void moving(std::mt19937& mt, Plot* array, const int l, const int vel);

public:
    Sky() {}
    Sky(const Sky&) = delete;
    Sky& operator=(const Sky&) = delete;
    const Plot* StaticSky() const { return sky; }
    const Plot* FastStars() const { return fast; }
    const Plot* SlowSky()   const { return slow; }
    void Move(std::mt19937& mt);
};



class CartoonObject :public Init
{
protected:
    int currentFrame{ 1 };
    int allFrames{ 0 };
    enumObjectStatus objectStatus = enumObjectStatus::isOnScreen;
    std::vector<Rect*> textureMainRects{ nullptr };
    std::vector<Rect*> objectMainRects{ nullptr };
    void initRects(const Texture* t, const Plot& center);

    CartoonObject(const Plot& center,
        const Texture* t,
        const int nomberFrames);
    CartoonObject(const CartoonObject&) = delete;
    CartoonObject& operator=(const CartoonObject&) = delete;

public:

    ~CartoonObject();

    void Tick();
    enumObjectStatus ObjectStatus() const { return objectStatus; }
    const std::vector<Rect*>& SourceRects() { return textureMainRects; }
    const std::vector<Rect*>& DestRects() { return objectMainRects; }
    SDL_Rect* CurrentSourceRect() const 
        { return textureMainRects[this->currentFrame]; }
    SDL_Rect* CurrentDestRect() const 
        { return objectMainRects[this->currentFrame]; }
};

class CartoonBlow : public CartoonObject
{
public:
    CartoonBlow(const TextureStore* store, const Plot& center) :
        CartoonObject(center, store->operator[](enumTextureType::cartoonBlow),
                        BLOW_FRAMES) {}
};


struct CartoonNode
{
    CartoonObject* cartoonObject{ nullptr };
    struct CartoonNode* next{ nullptr };

    ~CartoonNode()
    {
        delete cartoonObject;
        cartoonObject = nullptr;
    }
};

//Класс для хранения объектов - текстур из текста по типу
//PAUSE, Press Q to exit.. etc
class UItext: public Init
{
    private:
    SimpleObject** uiTextVector = nullptr;
    Plot startPos[static_cast<int>(enumGameFonts::all)] {0, 0};

    void initStartsPos(const TextureStore* store);
    bool initUiTextVector(const TextureStore* store);

    public:
    UItext(const TextureStore* store);
    ~UItext();
    SimpleObject* operator[](const enumGameFonts gameFont);
};


class FleetBase : public Init
{
protected:
    std::vector<Ship*> fleetVector;
    int currentFleetSize{};
    bool fleetIsOver{ false };
    explicit FleetBase(const int size);
    FleetBase(const FleetBase&) = delete;
    FleetBase& operator=(const FleetBase&) = delete;
public:
    ~FleetBase();
    std::vector<Ship*>& GetFleet() { return fleetVector; }
    void DecCurrentFleetSize() {currentFleetSize -= 1;}
    int GetCurrentFleetSize() const { return currentFleetSize; }
    bool IsFleetOver() const { return fleetIsOver; }

};

class Fleet_AlienOne : public FleetBase
{
protected:
    bool makeFleetOne(std::mt19937& mt, const Texture* t);
public:

    Fleet_AlienOne(std::mt19937& mt,
        const TextureStore* store,
        enumFleetKind kind,
        const int fleetSize);
};


//Класс для хранения таблиц Брадиса по синусу
class TableSin
{
private:
    const int tableLength = 180;
    double* vsin = nullptr;
public:
    TableSin();
    ~TableSin();
    double operator[](const int index);
};

//Класс для хранения таблицы по косинусу
class TableCos
{
    private:
    const int tableLength = 180;
    double* vcos = nullptr;

    public:
    TableCos();
    ~TableCos();
    double operator[](const int index);
};
