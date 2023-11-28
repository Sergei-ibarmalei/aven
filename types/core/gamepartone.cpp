#include "game.h"

static int heroBlowingTic = 0;
static int heroBlowAllTics = BLOW_FRAMES;

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




