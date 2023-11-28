#pragma once


#include "inits.h"
#include "rect.h"
#include "enums/enumtexture.h"
#include "enums/enumshipkind.h"
#include "enums/enumdigitspack.h"
#include "enums/enumtextingorder.h"
#include "enums/enumgamefon.h"
#include "enums/enumshlempack.h"
#include "enums/enumlasers.h"
#include "enums/enumcartoonblowframes.h"
#include "../const/mainrects.h"



class Texture 
{
private:
    Init init;
    SDL_Texture* sdlTexture = nullptr;
    Rect** mainRectsVector = nullptr;
    int   mainRectsVectorLength = 0;
    void initMainRectsVector(enumTextureType textureType);
    void initMainRectsVectorFonts(SDL_Surface* surface);

public:
    Texture(SDL_Texture* t,
        Rect** rectsVector,
        const int rectsVectorLength,
        enumTextureType textureType);
    //Текстура из текста
    Texture(SDL_Texture* t,
        Rect** rectsVector,
        SDL_Surface* surface);
    ~Texture();
    Texture& operator=(const Texture&) = delete;
    Texture(const Texture&) = delete;
    
    //Get mainRectVector[index]
    Rect* operator[](const int index) const;
    SDL_Texture* GetTexture() const { return sdlTexture; }
    bool Init_ok() const {return init.Init_ok();}

};