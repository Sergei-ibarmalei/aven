#pragma once

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "texture.h"
#include "enums/enumgamefonts.h"
#include "../const/colors.h"
#include "../const/fontconst.h"


class Sdl 
{
private:
    Init init;
    SDL_Renderer* renderer = nullptr;
    SDL_Window* window = nullptr;
    SDL_Event      e{};
    TTF_Font** fontsArray = nullptr;
    int        fontsArrayLength {0};

    bool initSdl(const char* appName, const int w, const int h);
    bool initFontsArray();

public:
    explicit Sdl(const char* name);
    ~Sdl();
    Sdl(const Sdl&) = delete;
    Sdl& operator=(const Sdl&) = delete;
    SDL_Renderer* Render() const { return renderer; }
    SDL_Event& Event() { return e; }

    Texture* MakeTexture(const char* texturePath, enumTextureType textureType);
    Texture* MakeTexture(enumGameFonts gameFonts, const char* textToTexture);
    bool Init_ok() const {return init.Init_ok();}

};