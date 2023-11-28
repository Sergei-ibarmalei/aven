#include "game.h"

void Game::draw_HUDlives()
{
#define THREE_LIVES_LEFT static_cast<int>(enumHudLives::three)
#define TWO_LIVES_LEFT   static_cast<int>(enumHudLives::two)
#define ONE_LIVE_LEFT    static_cast<int>(enumHudLives::one)
#define NO_LIVES_LEFT    static_cast<int>(enumHudLives::zero)


    switch (this->hud_lives->GetHeroLives())
    {
    case THREE_LIVES_LEFT:
    {
        SDL_RenderCopy(sdl->Render(),
            this->textureStore->
                operator[](enumTextureType::shlemsPack)->GetTexture(),
            this->textureStore->operator[](enumTextureType::shlemsPack)->
                operator[](static_cast<int>(enumShlemsPack::liveShlem)),
            &this->hud_lives->
            Lives_three()[static_cast<int>(enumHudLivesPosition::left)]);

        SDL_RenderCopy(sdl->Render(),
            this->textureStore->
                operator[](enumTextureType::shlemsPack)->GetTexture(),
            this->textureStore->operator[](enumTextureType::shlemsPack)->
                operator[](static_cast<int>(enumShlemsPack::liveShlem)),
            &this->hud_lives->
            Lives_three()[static_cast<int>(enumHudLivesPosition::center)]);

        SDL_RenderCopy(sdl->Render(),
            this->textureStore->
                operator[](enumTextureType::shlemsPack)->GetTexture(),
            this->textureStore->operator[](enumTextureType::shlemsPack)->
                operator[](static_cast<int>(enumShlemsPack::liveShlem)),
            &this->hud_lives->
            Lives_three()[static_cast<int>(enumHudLivesPosition::right)]);
        break;
    }
    case TWO_LIVES_LEFT:
    {
        SDL_RenderCopy(sdl->Render(),
            this->textureStore->
                operator[](enumTextureType::shlemsPack)->GetTexture(),
            this->textureStore->operator[](enumTextureType::shlemsPack)->
                operator[](static_cast<int>(enumShlemsPack::liveShlem)),
            &this->hud_lives->
            Lives_two()[static_cast<int>(enumHudLivesPosition::left)]);

        SDL_RenderCopy(sdl->Render(),
            this->textureStore->
                operator[](enumTextureType::shlemsPack)->GetTexture(),
            this->textureStore->operator[](enumTextureType::shlemsPack)->
                operator[](static_cast<int>(enumShlemsPack::liveShlem)),
            &this->hud_lives->
            Lives_two()[static_cast<int>(enumHudLivesPosition::center)]);

        SDL_RenderCopy(sdl->Render(),
            this->textureStore->
                operator[](enumTextureType::shlemsPack)->GetTexture(),
            this->textureStore->operator[](enumTextureType::shlemsPack)->
                operator[](static_cast<int>(enumShlemsPack::deadShlem)),
            &this->hud_lives->
            Lives_two()[static_cast<int>(enumHudLivesPosition::right)]);
        break;
    }
    case ONE_LIVE_LEFT:
    {
        SDL_RenderCopy(sdl->Render(),
            this->textureStore->
                operator[](enumTextureType::shlemsPack)->GetTexture(),
            this->textureStore->operator[](enumTextureType::shlemsPack)->
                operator[](static_cast<int>(enumShlemsPack::liveShlem)),
            &this->hud_lives->
            Lives_one()[static_cast<int>(enumHudLivesPosition::left)]);


        SDL_RenderCopy(sdl->Render(),
            this->textureStore->
                operator[](enumTextureType::shlemsPack)->GetTexture(),
            this->textureStore->operator[](enumTextureType::shlemsPack)->
                operator[](static_cast<int>(enumShlemsPack::deadShlem)),
            &this->hud_lives->
            Lives_one()[static_cast<int>(enumHudLivesPosition::center)]);


        SDL_RenderCopy(sdl->Render(),
            this->textureStore->
                operator[](enumTextureType::shlemsPack)->GetTexture(),
            this->textureStore->operator[](enumTextureType::shlemsPack)->
                operator[](static_cast<int>(enumShlemsPack::deadShlem)),
            &this->hud_lives->
            Lives_one()[static_cast<int>(enumHudLivesPosition::right)]);
        break;
    }

    case NO_LIVES_LEFT:
    {
        SDL_RenderCopy(sdl->Render(),
            this->textureStore->
                operator[](enumTextureType::shlemsPack)->GetTexture(),
            this->textureStore->operator[](enumTextureType::shlemsPack)->
                operator[](static_cast<int>(enumShlemsPack::deadShlem)),
            &this->hud_lives->
            Lives_zero()[static_cast<int>(enumHudLivesPosition::left)]);

        SDL_RenderCopy(sdl->Render(),
            this->textureStore->
                operator[](enumTextureType::shlemsPack)->GetTexture(),
            this->textureStore->operator[](enumTextureType::shlemsPack)->
                operator[](static_cast<int>(enumShlemsPack::deadShlem)),
            &this->hud_lives->
            Lives_zero()[static_cast<int>(enumHudLivesPosition::center)]);

        SDL_RenderCopy(sdl->Render(),
            this->textureStore->
                operator[](enumTextureType::shlemsPack)->GetTexture(),
            this->textureStore->operator[](enumTextureType::shlemsPack)->
                operator[](static_cast<int>(enumShlemsPack::deadShlem)),
            &this->hud_lives->
            Lives_zero()[static_cast<int>(enumHudLivesPosition::right)]);
        break;
    }
    default: {}
    }

#undef THREE_LIVES_LEFT 
#undef TWO_LIVES_LEFT   
#undef ONE_LIVE_LEFT    
#undef NO_LIVES_LEFT    
}

void Game::draw_HUDscore()
{
    for (auto s = 0; s < HUD_SCORE_LENGTH; s++)
    {
        SDL_RenderCopy(sdl->Render(),
            textureStore->
                operator[](enumTextureType::digitsPack)->GetTexture(),
            textureStore->
                operator[](enumTextureType::digitsPack)->
                operator[](this->hud_score->HudScore()[s]),
            &this->hud_score->HudScoreMainRects()[s]);
    }
}

void Game::draw_Sky()
{
    SDL_SetRenderDrawColor(this->sdl->Render(), 0xFF, 0xF5, 0xBF, 0xFF);
    for (auto s = 0; s < STATICSKYLENGTH; s++)
    {
        SDL_RenderDrawPoint(this->sdl->Render(), 
            this->sky->StaticSky()[s].x, 
            this->sky->StaticSky()[s].y);
    }
    for (auto s = 0; s < FASTSTARARRLENGTH; s++)
    {
        SDL_RenderDrawPoint(this->sdl->Render(), 
            this->sky->FastStars()[s].x, 
            this->sky->FastStars()[s].y);
    }
    for (auto s = 0; s < SLOWSTARARRLENGTH; s++)
    {
        SDL_RenderDrawPoint(this->sdl->Render(), 
            this->sky->SlowSky()[s].x, 
            this->sky->SlowSky()[s].y);
    }
    SDL_SetRenderDrawColor(sdl->Render(), 0, 0, 0, 0xFF);
}

void Game::draw_MainMenu()
{
#define int_ static_cast<int>
    switch (mainmenu->GetChoise())
    {
        case int_(enumMainMenuChoise::new_game):
        {
            DrawSimpleObject(sdl,
                *mainmenu->operator[](enumTextingOrder::red_newgame),
                textureStore->operator[](enumTextureType::mainmenuText));
            DrawSimpleObject(sdl,
                *mainmenu->operator[](enumTextingOrder::black_rules),
                textureStore->operator[](enumTextureType::mainmenuText));
            DrawSimpleObject(sdl,
                *mainmenu->operator[](enumTextingOrder::black_exit),
                textureStore->operator[](enumTextureType::mainmenuText));
            break;
        }
        case int_(enumMainMenuChoise::rules):
        {
            DrawSimpleObject(sdl,
                *mainmenu->operator[](enumTextingOrder::black_newgame),
                textureStore->operator[](enumTextureType::mainmenuText));
            DrawSimpleObject(sdl,
                *mainmenu->operator[](enumTextingOrder::red_rules),
                textureStore->operator[](enumTextureType::mainmenuText));
            DrawSimpleObject(sdl,
                *mainmenu->operator[](enumTextingOrder::black_exit),
                textureStore->operator[](enumTextureType::mainmenuText));
            break;
        }
        case int_(enumMainMenuChoise::exit):
        {
            DrawSimpleObject(sdl,
                *mainmenu->operator[](enumTextingOrder::black_newgame),
                textureStore->operator[](enumTextureType::mainmenuText));
            DrawSimpleObject(sdl,
                *mainmenu->operator[](enumTextingOrder::black_rules),
                textureStore->operator[](enumTextureType::mainmenuText));
            DrawSimpleObject(sdl,
                *mainmenu->operator[](enumTextingOrder::red_exit),
                textureStore->operator[](enumTextureType::mainmenuText));
            break;
        }
    }
#undef int_
}

void Game::drawGamePause()
{
		DrawSimpleObject(sdl, *uiText->operator[](enumGameFonts::pause),
			textureStore->operator[](enumTextureType::fontPause));
		DrawSimpleObject(sdl,*uiText->operator[](enumGameFonts::pressQ),
		textureStore->operator[](enumTextureType::fontPressQ));
}

void Game::drawGameOver()
{
		DrawSimpleObject(sdl, *uiText->operator[](enumGameFonts::gameover),
			textureStore->operator[](enumTextureType::fontGameover));
		DrawSimpleObject(sdl,*uiText->operator[](enumGameFonts::pressEsc),
		textureStore->operator[](enumTextureType::fontPressEsc));
}


void Game::drawPartOnePause()
{
		sky->Move(mt);
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
		draw_HUDlives();
		draw_HUDscore();
		DrawSimpleObject(sdl,
			*fon,
			textureStore->operator[](enumTextureType::gameFon));
		drawGamePause();
		SDL_RenderPresent(sdl->Render());	
}
