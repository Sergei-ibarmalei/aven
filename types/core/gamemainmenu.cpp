#include "game.h"




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



