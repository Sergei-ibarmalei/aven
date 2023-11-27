#pragma once

#include "types.h"
#include "video.h"

class Game : public Init
{
private:
	std::mt19937  mt{ static_cast<std::mt19937::result_type>(
		std::chrono::steady_clock::now().time_since_epoch().count()) };
	TableSin*     tableSin{nullptr};
	TableCos*     tableCos{nullptr};
	Sdl*          sdl{ nullptr };
	TextureStore* textureStore{ nullptr };
	Plot          heroStart{ 0, 0 };
	Hero*         hero{ nullptr };
	GameFon*      fon{ nullptr };
	HUD_lives*    hud_lives{ nullptr };
	HUD_score*    hud_score{ nullptr };
	StoreLaser<Laser>*           heroStoreLaser{ nullptr };
	StoreLaser<Laser>*           firstfleetStoreLaser{nullptr};
	StoreCartoon<CartoonObject>* storeCartoon{ nullptr };
	Fleet_AlienOne*              fleet_AlienOne{ nullptr };
	Sky*          sky{ nullptr };
	MainMenu*     mainmenu{ nullptr };

	GameState*    gameState{ nullptr };
	UItext*       uiText {nullptr};
	Plot          heroIntroStartPoint{};

	bool restart_flag {false};


	void draw_HUDlives();
	void draw_HUDscore();
	void draw_Sky();
	void draw_MainMenu();

	void startInit();
	void initHeroIntroStartPoint();
	void gameStateInit();
	void flow();
	void inMainMenu();
	void inPartOne();
	void partOneGameOver();
	void partOneIntro();

	void checkFirstFleetVSLaser(Node<Laser>* n);
	void checkHeroVSLaser(Node<Laser>* n);
	void checkFirstFleetMayShoot();
	void firstFleetMove();
	void drawGamePause();
	void drawPartOnePause();
	void drawGameOver();

	bool restartCore();

	void partOneAfterHeroCrash();
	bool reinitAlienFleetOne(const int size);
	void deletingFleet(FleetBase* fleet);
	void cleaningStoreLaser(Node<Laser>* n);
	bool reincarnateHero();

	void doBlowHero(); //уничтожаем героя


public:
	Game();
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	~Game();
};