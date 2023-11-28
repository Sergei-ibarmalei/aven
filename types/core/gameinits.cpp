#include "game.h"

void Game::startInit()
{
	sdl = new Sdl{ "appTest" };
	if (sdl->Init_ok() == false) { init.Negate(); return; }
	tableSin = new TableSin{};
	tableCos = new TableCos{};
	textureStore = new TextureStore{ sdl };
	if (textureStore->Init_ok() == false) { init.Negate(); return; }
	fon = new GameFon{ textureStore->operator[](enumTextureType::gameFon) };
	if (fon->Init_ok() == false) { init.Negate(); return; }
	hud_lives =
		new HUD_lives{ textureStore->operator[](enumTextureType::shlemsPack) };
	if (hud_lives->Init_ok() == false) { init.Negate(); return; }

	hud_score = new HUD_score{};
	heroStoreLaser= new StoreLaser<Laser>;
	firstfleetStoreLaser = new StoreLaser<Laser>;
	storeCartoon = new StoreCartoon<CartoonObject>;
	fleet_AlienOne = new Fleet_AlienOne{ mt,
										textureStore,
										enumFleetKind::alienOneFleet,
										ALIENONEFLEET_SIZE };
	if (fleet_AlienOne->Init_ok() == false) { init.Negate(); return; }
	sky = new Sky{};
	mainmenu =
		new MainMenu{ textureStore->operator[](enumTextureType::mainmenuText) };
	if (mainmenu->Init_ok() == false) { init.Negate(); return; }

	gameState = new GameState{};
	gameStateInit();
	initHeroIntroStartPoint();
	hero = new Hero{ textureStore->operator[](enumTextureType::ships),
		heroIntroStartPoint };
	if (hero->Init_ok() == false) { init.Negate(); return; }

	uiText = new UItext{textureStore};
}


void Game::gameStateInit()
{
	gameState->heroState.hero_isAlive = true;
	gameState->heroState.hero_isDead =  false;
	gameState->gameOver =               false;
	gameState->heroIntro =              true;
	gameState->inGamePause =            false;
	gameState->inMainMenu =             true;
	gameState->goingOut =               false;
	gameState->inPartOne =              false;
	gameState->gamePause =              false;
	gameState->toSystem =               false;

}

void Game::initHeroIntroStartPoint()
{
	heroIntroStartPoint.x =
		awindow.x -  textureStore->
		operator[](enumTextureType::ships)->
		operator[](static_cast<int>(enumShipKind::hero))->w;
	heroIntroStartPoint.y =
		(MAINWINDOW_H >> 1) - 
		(textureStore->operator[](enumTextureType::ships)->
		operator[](static_cast<int>(enumShipKind::hero))->h >> 1);
}
