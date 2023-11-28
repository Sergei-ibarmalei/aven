#include "game.h"

Game::Game()
{
	startInit();
	if (init.Init_ok() == false) return;
	flow();

}

Game::~Game()
{
	delete tableSin;       		 tableSin = nullptr;
	delete tableCos;	   		 tableCos = nullptr;
	delete sdl;            		 sdl = nullptr;
	delete textureStore;   		 textureStore = nullptr;
	delete hero;           		 hero = nullptr;
	delete fon;            		 fon = nullptr;
	delete hud_lives;      		 hud_lives = nullptr;
	delete hud_score;      		 hud_score = nullptr;
	delete heroStoreLaser; 		 heroStoreLaser = nullptr;
	delete firstfleetStoreLaser; firstfleetStoreLaser = nullptr;
	delete storeCartoon;   		 storeCartoon = nullptr;
	delete fleet_AlienOne; 		 fleet_AlienOne = nullptr;
	delete sky;            		 sky = nullptr;
	delete mainmenu;       		 mainmenu = nullptr;
	delete gameState;      		 gameState = nullptr;
}

bool Game::restartCore()
{
	cleaningStoreLaser(heroStoreLaser->First());
	cleaningStoreLaser(firstfleetStoreLaser->First());
	heroStoreLaser->CheckStoreForGone();
	firstfleetStoreLaser->CheckStoreForGone();
	delete storeCartoon; storeCartoon = nullptr;
	storeCartoon = new StoreCartoon<CartoonObject>;
	deletingFleet(fleet_AlienOne);
	if (!reinitAlienFleetOne(ALIENONEFLEET_SIZE)) return false;
	if (!reincarnateHero()) return false;

	hud_lives->Reinit();
	hud_score->ResetGameScore();
	gameStateInit();
	return true;
}

void Game::flow()
{
	while (!gameState->toSystem)
	{
		if (gameState->inMainMenu) inMainMenu();
		if (gameState->inPartOne) inPartOne();
	}
}

//уничтожаем героя
void Game::doBlowHero()
{
			//устанавливаем взрыв на месте героя
			storeCartoon->Push(new CartoonBlow{textureStore,
				hero->GetCenter()});
			gameState->heroState.hero_isDead = true;
			gameState->heroState.hero_isAlive = false;
}



void Game::firstFleetMove()
{
	for (auto& ship: fleet_AlienOne->GetFleet())
	{
		ship->Move();
		if (gameState->heroState.hero_isAlive &&  *hero == *ship)
		{
			ship->NowIsCrashed();
			hero->NowIsCrashed();
			hud_lives->DecHeroLives();
			if (hud_lives->GetHeroLives() < 1)
			{
				storeCartoon->Push(new CartoonBlow{textureStore,
				hero->GetCenter()});
				storeCartoon->Push(new CartoonBlow{textureStore,
				ship->GetCenter()});
				gameState->gameOver = true;
			}
			return;
		}
	}
}

bool Game::reinitAlienFleetOne(const int fleetsize)
{
	fleet_AlienOne = new Fleet_AlienOne{ mt,
										textureStore,
										enumFleetKind::alienOneFleet,
										fleetsize};
	if (fleet_AlienOne->Init_ok() == false) return false;
	return true; 
}

void Game::deletingFleet(FleetBase* fleet)
{
	for (auto ship: fleet->GetFleet())
	{
		if (ship->ObjectStatus() != enumObjectStatus::isOnScreen) continue;
		ship->NowIsCrashed();
	}
	for (auto& ship: fleet->GetFleet())
	{
		delete ship; ship = nullptr;
	}
	delete fleet; fleet = nullptr;
}

void Game::cleaningStoreLaser(Node<Laser>* n)
{
	if (n == nullptr) return;
	n->object->NowIsCrashed();
	cleaningStoreLaser(n->next);
}

bool Game::reincarnateHero()
{
	hero->NowIsCrashed();
	delete hero;
	hero = nullptr;
	hero = new Hero{ textureStore->operator[](enumTextureType::ships),
		heroIntroStartPoint };
	if (hero->Init_ok() == false) return false;
	gameState->heroState.hero_isDead = false;
	gameState->heroState.hero_isAlive = true;
	gameState->heroIntro = true;
	return true;
}
