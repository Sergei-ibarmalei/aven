#pragma once

#include "inits.h"
#include "texture.h"
#include "sdltype.h"


class TextureStore
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
    Init init;
    Texture** store = nullptr;
    int       storeLength = 0;
    bool      fillStore(Sdl* sdl);
public:
    explicit TextureStore(Sdl* sdl);
    TextureStore(const TextureStore&) = delete;
    TextureStore& operator=(const TextureStore&) = delete;

    Texture* operator[](enumTextureType textureType) const;
    ~TextureStore();
    bool Init_ok() const {return init.Init_ok();}

};