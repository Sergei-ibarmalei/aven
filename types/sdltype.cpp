#include "sdltype.h"

Sdl::Sdl(const char* appName)
{
    appName == nullptr ? init_ok = false : init_ok = init(appName,
        MAINWINDOW_W, MAINWINDOW_H);
}



bool Sdl::init(const char* appName, const int w, const int h)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return false;
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) return false;

    window = SDL_CreateWindow(appName,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        w,
        h,
        SDL_WINDOW_SHOWN);
    if (!window)
    {
        std::cout << "Cannot initialize window, abort.\n";
        init_ok = false;
        return init_ok;
    }

    renderer = SDL_CreateRenderer(window,
        -1,
        SDL_RENDERER_ACCELERATED |
        SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
    {
        std::cout << "Cannot initiate renderer, abort.\n";
        init_ok = false;
        return init_ok;
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        std::cout << "SDL_image could not initialize, abort.\n";
        init_ok = false;
        return init_ok;
    }

    if (TTF_Init() == -1)
    {
        std::cout << "SDL_ttf error: " << TTF_GetError() << std::endl;
        return false;
    }

    if (!initFontsArray())
    {
        std::cout << "Cannot make font textures, abort.\n";
        return false;
    }
#ifdef SHOWCURSOR
    SDL_ShowCursor(SDL_DISABLE);
#endif
    return true;
}

Texture* Sdl::MakeTexture(enumGameFonts gameFonts,
    const char* textToTexture)
{
#define int_ static_cast<int>
    SDL_Surface* surface = nullptr;
    SDL_Texture* sdlTexture = nullptr;
    Texture*     texture = nullptr;
    Rect**       mainRectsVector = new Rect* [1];
    switch (gameFonts)
    {
        case enumGameFonts::pause:
        {
            surface =
            TTF_RenderText_Solid(fontsArray[int_(enumGameFonts::pause)],
            textToTexture, {MAROON});
            break;
        }
        case enumGameFonts::pressQ:
        {
            surface =
            TTF_RenderText_Solid(fontsArray[int_(enumGameFonts::pressQ)],
            textToTexture, {PEACH_PUFF});
            break;
        }
        case enumGameFonts::pressEsc:
        {
            surface =
            TTF_RenderText_Solid(fontsArray[int_(enumGameFonts::pressEsc)],
            textToTexture, {PEACH_PUFF});
            break;
        }
        case enumGameFonts::de:
        {
            surface =
            TTF_RenderText_Solid(fontsArray[int_(enumGameFonts::de)],
            textToTexture, {TOMATO});
            break;
        }
        case enumGameFonts::ad:
        {
            surface =
            TTF_RenderText_Solid(fontsArray[int_(enumGameFonts::ad)],
            textToTexture, {TOMATO});
            break;
        }
        case enumGameFonts::gameover:
        {
            surface =
            TTF_RenderText_Solid(fontsArray[int_(enumGameFonts::gameover)],
            textToTexture, {MAROON});
            break;
        }
        default: {}
    }
    if (!surface)
    {
        std::cout << "Cannot create surface from text, abort.\n";
        return nullptr;
    }
    sdlTexture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!sdlTexture)
    {
        std::cout << "Cannot create texture from text surface, abort.\n";
        return nullptr;
    }
    texture = new Texture(sdlTexture, mainRectsVector, surface);
    if (texture->Init_ok() == false)
    {
        delete texture;
        texture = nullptr;
        return texture;
    }
    return texture;

#undef int_
}


Texture* Sdl::MakeTexture(const char* texturePath, enumTextureType textureType)
{
    if (!texturePath) return nullptr;
    SDL_Texture* sdlTexture = IMG_LoadTexture(this->renderer,
        texturePath);

    Texture* texture = nullptr;
    Rect** mainRectsVector = nullptr;
    switch (textureType)
    {
#define int_ static_cast<int>

    case enumTextureType::ships:
    {
        mainRectsVector = new Rect * [int_(enumShipKind::all)];
        texture = new Texture(sdlTexture, mainRectsVector,
            int_(enumShipKind::all), textureType);
        if (texture->Init_ok() == false)
        {
            delete texture;
            texture = nullptr;
        }
        break;
    }

    case enumTextureType::gameFon:
    {
        mainRectsVector = new Rect * [int_(enumFon::all)];
        texture = new Texture(sdlTexture, mainRectsVector,
            int_(enumFon::all), textureType);
        if (texture->Init_ok() == false)
        {
            delete texture;
            texture = nullptr;
        }
        break;
    }

    case enumTextureType::digitsPack:
    {
        mainRectsVector = new Rect * [int_(enumDigitsPack::all)];
        texture = new Texture(sdlTexture, mainRectsVector,
            int_(enumDigitsPack::all), textureType);
        if (texture->Init_ok() == false)
        {
            delete texture;
            texture = nullptr;
        }
        break;
    }

    case enumTextureType::shlemsPack:
    {
        mainRectsVector = new Rect * [int_(enumShlemsPack::all)];
        texture = new Texture(sdlTexture, mainRectsVector,
            int_(enumShlemsPack::all), textureType);
        if (texture->Init_ok() == false)
        {
            delete texture;
            texture = nullptr;
        }
        break;
    }

    case enumTextureType::lasersPack:
    {
        mainRectsVector = new Rect * [int_(enumLasers::all)];
        texture = new Texture(sdlTexture, mainRectsVector,
            int_(enumLasers::all), textureType);
        if (texture->Init_ok() == false)
        {
            delete texture;
            texture = nullptr;
        }
        break;
    }
    case enumTextureType::cartoonBlow:
    {
        mainRectsVector = new Rect * [int_(enumCartoonBloowFrames::all)];
        texture = new Texture(sdlTexture, mainRectsVector,
            int_(enumCartoonBloowFrames::all), textureType);
        if (texture->Init_ok() == false)
        {
            delete texture;
            texture = nullptr;
        }
        break;
    }

    case enumTextureType::mainmenuText:
    {
        mainRectsVector = new Rect * [int_(enumTextingOrder::all)];
        texture = new Texture(sdlTexture, mainRectsVector,
            int_(enumTextingOrder::all), textureType);
        if (texture->Init_ok() == false)
        {
            delete texture;
            texture = nullptr;
        }
        break;
    }
    default: {}
#undef int_
    }

    return texture;
}

bool Sdl::initFontsArray()
{
#define int_ static_cast<int>
    fontsArrayLength = int_(enumGameFonts::all);
    fontsArray = new TTF_Font * [fontsArrayLength] {nullptr};
    fontsArray[int_(enumGameFonts::pause)] =
        TTF_OpenFont(GAMEFONT, PAUSE_HEIGHT);
    if (fontsArray[int_(enumGameFonts::pause)] == nullptr) return false;
    fontsArray[int_(enumGameFonts::pressQ)] =
        TTF_OpenFont(GAMEFONT, PRESSQ_HEIGHT);
    if (fontsArray[int_(enumGameFonts::pressQ)] == nullptr) return false;
    fontsArray[int_(enumGameFonts::pressEsc)] =
        TTF_OpenFont(GAMEFONT, PRESSESC_HEIGHT);
    if (fontsArray[int_(enumGameFonts::pressEsc)] == nullptr) return false;

    fontsArray[int_(enumGameFonts::de)] =
        TTF_OpenFont(GAMEFONT, DE_HEIGHT);
    if (fontsArray[int_(enumGameFonts::de)] == nullptr) return false;
    fontsArray[int_(enumGameFonts::ad)] =
        TTF_OpenFont(GAMEFONT, AD_HEIGHT);
    if (fontsArray[int_(enumGameFonts::ad)] == nullptr) return false;
    fontsArray[int_(enumGameFonts::gameover)] =
        TTF_OpenFont(GAMEFONT,GAMEOVER_HEIGHT);
    if (fontsArray[int_(enumGameFonts::gameover)] == nullptr) return false;
    return true;

#undef int_

}

Sdl::~Sdl()
{
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
    SDL_DestroyWindow(window);
    window = nullptr;
    if (fontsArray)
    {
        for (int f = 0; f < fontsArrayLength; f++)
        {
           if (fontsArray[f]) TTF_CloseFont(fontsArray[f]);
           fontsArray[f] = nullptr;
        }
    }
    delete fontsArray;
    fontsArray = nullptr;
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

