#include "core.h"

static int heroBlowingTic = 0;
static int heroBlowAllTics = BLOW_FRAMES;

Game::Game()
{
	startInit();
	if (init_ok == false) return;
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

void Game::flow()
{
	while (!gameState->toSystem)
	{
		if (gameState->inMainMenu) inMainMenu();
		if (gameState->inPartOne) inPartOne();
	}
}

void Game::inMainMenu()
{
	while (!gameState->toSystem)
	{
		SDL_SetRenderDrawColor(this->sdl->Render(), 0x0, 0x0, 0x0, 0xff);
		SDL_RenderClear(this->sdl->Render());
		while (SDL_PollEvent(&this->sdl->Event()))
		{
			if (this->sdl->Event().type == SDL_QUIT) 
				gameState->toSystem = true;
			else if (this->sdl->Event().type == SDL_KEYDOWN &&
					this->sdl->Event().key.repeat == 0)
			{
				switch (this->sdl->Event().key.keysym.sym)
				{
					case SDLK_UP:
					{
						this->mainmenu->PrevChoise();
						break;
					}
					case SDLK_DOWN:
					{
						this->mainmenu->NextChoise();
						break;
					}
					case SDLK_RETURN:
					{
						if (this->mainmenu->GetChoise() ==
						static_cast<int>(enumMainMenuChoise::exit))
						{
							gameState->toSystem = true;
							continue;
						}
						if (this->mainmenu->GetChoise() ==
						static_cast<int>(enumMainMenuChoise::new_game))
						{
							gameState->inPartOne = true;
							return;
						}
						break;
					}
				}
			}
		}
		draw_MainMenu();
		SDL_RenderPresent(this->sdl->Render());
		
	}
}

void Game::inPartOne()
{
	if (restart_flag)
	{
		restart_flag = false;
		if (!restartCore())
		{
			gameState->toSystem = true; return;
		}
	}	
	while (!gameState->goingOut && !gameState->toSystem)
	{
		
		if (gameState->gameOver)
		{
			partOneGameOver();
			if (gameState->toSystem) return;
			if (!restartCore())
			{
				gameState->toSystem = true; return;
			}
			return;
		}
		if (gameState->heroIntro)
		{
			partOneIntro();
			continue;
		}


		SDL_SetRenderDrawColor(this->sdl->Render(), 0x0, 0x0, 0x0, 0xff);
		SDL_RenderClear(this->sdl->Render());
		while (SDL_PollEvent(&this->sdl->Event()))
		{
			if (this->sdl->Event().type == SDL_QUIT)
			{
				gameState->toSystem = true;
				return;
			} 
			else if (this->sdl->Event().type == SDL_KEYDOWN &&
				this->sdl->Event().key.repeat == 0)
			{
				switch (this->sdl->Event().key.keysym.sym)
				{
					case SDLK_ESCAPE:
					{
						if (gameState->gamePause)
						{
							gameState->gamePause = false;
							continue;
						}
						if (!gameState->gamePause)
						{
							gameState->gamePause = true;
							continue;
						}
						break;
					}
					case SDLK_q:
					{
						if (gameState->gamePause)
						{
							gameState->heroIntro = false;
							gameState->inPartOne = false;
							gameState->goingOut = true;
							gameState->inMainMenu = true;
							restart_flag = true;
							continue;
						}
						break;
					}
					case SDLK_SPACE:
					{
						heroStoreLaser->Push(new HeroLaser{ 
							textureStore->
							operator[](enumTextureType::lasersPack),
							*hero->GetLaserStart()});
						break;
					}
					case SDLK_UP:
					{
						hero->MoveUp(HERONORMAL_VELY);
						break;
					}
					case SDLK_DOWN:
					{
						hero->MoveDown(HERONORMAL_VELY);
						break;
					}
					case SDLK_RIGHT:
					{
						hero->MoveRight(HERONORMAL_VELX);
						break;
					}
					case SDLK_LEFT:
					{
						hero->MoveLeft(HERONORMAL_VELX);
						break;
					}
					case SDLK_0:
					{
						std::cout << "hero eshelon: [" <<
						hero->GetHeroEshelon().ceiling << ' ' <<
						hero->GetHeroEshelon().floor << "]\n";
						break;
					}
					default: {}

				}
			}
			else if (sdl->Event().type == SDL_KEYUP &&
				sdl->Event().key.repeat == 0)
			{
				hero->Stop();
			}
		}
		if (gameState->gamePause)
		{
			drawPartOnePause();
			continue;
		}
		hero->Move();

		heroStoreLaser->Move();
		firstfleetStoreLaser->Move();
		checkFirstFleetMayShoot();

		heroStoreLaser->CheckStoreForGone();
		firstfleetStoreLaser->CheckStoreForGone();

		storeCartoon->CheckStoreForGone();
		checkFirstFleetVSLaser(heroStoreLaser->First());
		checkHeroVSLaser(firstfleetStoreLaser->First());
		firstFleetMove();
		sky->Move(this->mt);
		draw_Sky();
		DrawComplexObject(sdl,
			hero,
			textureStore->operator[](enumTextureType::ships));

		DrawLasers(sdl, 
			heroStoreLaser->FirstConst(), 
			textureStore->operator[](enumTextureType::lasersPack));
		DrawLasers(sdl,
			firstfleetStoreLaser->FirstConst(),
			textureStore->operator[](enumTextureType::lasersPack));
		DrawAlienOneFleetV(sdl, 
			fleet_AlienOne, 
			textureStore->operator[](enumTextureType::ships));
		DrawCartoons(sdl, 
			storeCartoon->FirstConst(), 
			textureStore->operator[](enumTextureType::cartoonBlow));
		storeCartoon->Tick();

		draw_HUDlives();
		draw_HUDscore();
		DrawSimpleObject(sdl,
			*fon,
			textureStore->operator[](enumTextureType::gameFon));

		//если герой погиб
		if (gameState->heroState.hero_isDead)
		{
			//отсчитываем кадры взрыва для отрисовки
			if (heroBlowingTic < heroBlowAllTics) heroBlowingTic++;
		}
		//если герой погиб и взрыв отрисован полностью
		if (gameState->heroState.hero_isDead && 
			heroBlowingTic == heroBlowAllTics)
		{
			heroBlowingTic = 0;
			partOneAfterHeroCrash();
			continue;
		}	
		SDL_RenderPresent(sdl->Render());
	}
}



void Game::partOneGameOver()
{
	while (!gameState->toSystem && !gameState->goingOut)
	{
		SDL_SetRenderDrawColor(sdl->Render(), 0x0, 0x0, 0x0, 0xff);
		SDL_RenderClear(sdl->Render());
		while (SDL_PollEvent(&sdl->Event()))
		{
			if (sdl->Event().type == SDL_QUIT)
			{
				gameState->toSystem = true; return;
			}
			else if (sdl->Event().type == SDL_KEYDOWN &&
				sdl->Event().key.repeat == 0)
			{
				switch (sdl->Event().key.keysym.sym)
				{
					case SDLK_ESCAPE:
					case SDLK_q:
					{
						gameState->goingOut = true;
						break;
					}
				}
			}
		}
		sky->Move(mt);
		draw_Sky();
		draw_HUDlives();
		draw_HUDscore();
		drawGameOver();
		DrawSimpleObject(sdl, 
			         *fon, 
			          textureStore->operator[](enumTextureType::gameFon));
		DrawCartoons(sdl, 
			storeCartoon->FirstConst(), 
			textureStore->operator[](enumTextureType::cartoonBlow));
		storeCartoon->Tick();
		SDL_RenderPresent(sdl->Render());	
	}
}

void Game::partOneIntro()
{
	while (gameState->heroIntro && !gameState->toSystem)
	{
		SDL_SetRenderDrawColor(sdl->Render(), 0x0, 0x0, 0x0, 0xff);
		SDL_RenderClear(sdl->Render());
		while (SDL_PollEvent(&sdl->Event()))
		{
			if (sdl->Event().type == SDL_QUIT)
			{
				gameState->heroIntro = false;
				gameState->toSystem = true;
				return;
			} 
			else if (sdl->Event().type == SDL_KEYDOWN &&
				sdl->Event().key.repeat == 0)
			{
				switch (this->sdl->Event().key.keysym.sym)
				{
					case SDLK_ESCAPE:
					{
						if (gameState->gamePause == true)
						{
							gameState->gamePause = false;
							continue;
						}
						if (gameState->gamePause == false)
						{
							gameState->gamePause = true;
							continue;
						}
						break;
					}
					case SDLK_q:
					{
						if (gameState->gamePause == true)
						{
							gameState->heroIntro = false;
							gameState->inPartOne = false;
							gameState->goingOut = true;
							gameState->inMainMenu = true;
							restart_flag= true;
							continue;
						}
						break;
					}
				}
			}
		}
		if (gameState->gamePause == false)
			hero->MoveIntro(gameState);
		sky->Move(mt);
		draw_Sky();
		DrawComplexObject(sdl, 
						  hero, 
						  textureStore->operator[](enumTextureType::ships));

		draw_HUDlives();
		draw_HUDscore();
		if (gameState->gamePause) drawGamePause();
		DrawSimpleObject(sdl, 
			         *fon, 
			          textureStore->operator[](enumTextureType::gameFon));
		SDL_RenderPresent(sdl->Render());
	}


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

//проверка на попадание лазером алиена в героя
void Game::checkHeroVSLaser(Node<Laser>* n)
{
	if (n == nullptr) return;
	if (n->object->ObjectStatus() == enumObjectStatus::isOnScreen)
	{
		if (*n->object == *hero)
		{
			n->object->NowIsCrashed();
			hero->NowIsCrashed();
			hud_lives->DecHeroLives();
			if (hud_lives->GetHeroLives() < 1)
			{
				storeCartoon->Push(new CartoonBlow{textureStore,
				hero->GetCenter()});
				gameState->gameOver = true;
				return;
			}

			doBlowHero();
			return;
		}

	}
	checkHeroVSLaser(n->next);
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

//проверка первого флота на сбитие от лазера героя
void Game::checkFirstFleetVSLaser(Node<Laser>* n)
{
	if (n == nullptr) return;
	for (auto& ship: fleet_AlienOne->GetFleet())
	{
		if (ship->ObjectStatus() == enumObjectStatus::isReady) break;
		if (ship->ObjectStatus() == enumObjectStatus::isCrashed) continue;

		if (*n->object == *ship)
		{
            ship->NowIsCrashed();
            fleet_AlienOne->DecCurrentFleetSize();
            hud_score->SetScore(ship->GetScore());
            n->object->NowIsCrashed();
            storeCartoon->
				Push(new CartoonBlow(textureStore, ship->GetCenter()));
		}
	}
	checkFirstFleetVSLaser(n->next);

}

//проверка первого флота на возможность выстрела
void Game::checkFirstFleetMayShoot()
{
	for (auto& ship: fleet_AlienOne->GetFleet())
	{
		if (ship->ObjectStatus() == enumObjectStatus::isReady) break;
		if (ship->ObjectStatus() == enumObjectStatus::isCrashed) continue;

		//если алиен может выстрелить и находится в эшелоне героя
		if (static_cast<Alien_one*>(ship)->ThisAlienMayShoot() &&
			ship->InEshelon(hero->GetHeroEshelon()))
		{
			//если пролетел героя, то не стреляет
			if (ship->GetCenter().x < hero->GetCenter().x) continue;

			//Делаем выстрел
			firstfleetStoreLaser->Push(new FirstFleetAlienLaser{textureStore->
			operator[](enumTextureType::lasersPack), *ship->GetLaserStart()});
			//Запрещаем делать выстрел до следующего раза
			static_cast<Alien_one*>(ship)->ThisAlienCantShoot();
		}
	}
}

void Game::partOneAfterHeroCrash()
{
	int currentFleetSize = fleet_AlienOne->GetCurrentFleetSize();
	if (currentFleetSize <= 3) currentFleetSize = 3;
	cleaningStoreLaser(heroStoreLaser->First());
	cleaningStoreLaser(firstfleetStoreLaser->First());
	heroStoreLaser->CheckStoreForGone();
	firstfleetStoreLaser->CheckStoreForGone();
	deletingFleet(fleet_AlienOne);
	if (!reinitAlienFleetOne(currentFleetSize))
	{
		gameState->gameOver = true; return;
	}
	if (!reincarnateHero())
	{
		gameState->gameOver = true; return;
	}
	gameState->heroIntro = true;
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

