#include "texturestore.h"


TextureStore::TextureStore(Sdl* sdl)
{
    if (!sdl) { init_ok = false; return; }
    storeLength = static_cast<int>(enumTextureType::all);
    store = new Texture * [storeLength] {nullptr};
    if (!fillStore(sdl))
    {
        init_ok = false;
    }
}



Texture* TextureStore::operator[](enumTextureType textureType) const
{
    if (textureType < enumTextureType::ships ||
        textureType >= enumTextureType::all) return nullptr;
    return store[static_cast<int>(textureType)];
}

bool TextureStore::fillStore(Sdl* sdl)
{
#define int_ static_cast<int>

    store[int_(enumTextureType::ships)] =
        sdl->MakeTexture(gameTexturesPaths[int_(enumTextureType::ships)],
            enumTextureType::ships);
    if (!store[int_(enumTextureType::ships)]) return false;

    store[int_(enumTextureType::gameFon)] =
        sdl->MakeTexture(gameTexturesPaths[int_(enumTextureType::gameFon)],
            enumTextureType::gameFon);
    if (!store[int_(enumTextureType::gameFon)]) return false;

    store[int_(enumTextureType::digitsPack)]
        = sdl->
            MakeTexture(gameTexturesPaths[int_(enumTextureType::digitsPack)],
            enumTextureType::digitsPack);
    if (!store[int_(enumTextureType::digitsPack)]) return false;

    store[int_(enumTextureType::shlemsPack)] =
        sdl->MakeTexture(gameTexturesPaths[int_(enumTextureType::shlemsPack)],
            enumTextureType::shlemsPack);
    if (!store[int_(enumTextureType::shlemsPack)]) return false;

    store[int_(enumTextureType::lasersPack)] =
        sdl->MakeTexture(gameTexturesPaths[int_(enumTextureType::lasersPack)],
            enumTextureType::lasersPack);
    if (!store[int_(enumTextureType::lasersPack)]) return false;

    store[int_(enumTextureType::cartoonBlow)] =
        sdl->MakeTexture(gameTexturesPaths[int_(enumTextureType::cartoonBlow)],
            enumTextureType::cartoonBlow);
    if (!store[int_(enumTextureType::cartoonBlow)]) return false;

    store[int_(enumTextureType::mainmenuText)] =
        sdl->
            MakeTexture(gameTexturesPaths[int_(enumTextureType::mainmenuText)],
            enumTextureType::mainmenuText);
    if (!store[int_(enumTextureType::mainmenuText)]) return false;

    store[int_(enumTextureType::fontPause)] =
        sdl->MakeTexture(enumGameFonts::pause,
        gameTexturesPaths[int_(enumTextureType::fontPause)]);
    if (!store[int_(enumTextureType::fontPause)]) return false;

    store[int_(enumTextureType::fontPressQ)] =
        sdl->MakeTexture(enumGameFonts::pressQ,
        gameTexturesPaths[int_(enumTextureType::fontPressQ)]);
    if (!store[int_(enumTextureType::fontPressQ)]) return false;

    store[int_(enumTextureType::fontPressEsc)] =
        sdl->MakeTexture(enumGameFonts::pressEsc,
        gameTexturesPaths[int_(enumTextureType::fontPressEsc)]);
    if (!store[int_(enumTextureType::fontPressEsc)]) return false;

    store[int_(enumTextureType::fontDE)] =
        sdl->MakeTexture(enumGameFonts::de,
        gameTexturesPaths[int_(enumTextureType::fontDE)]);
    if (!store[int_(enumTextureType::fontDE)]) return false;

    store[int_(enumTextureType::fontAD)] =
        sdl->MakeTexture(enumGameFonts::ad,
        gameTexturesPaths[int_(enumTextureType::fontAD)]);
    if (!store[int_(enumTextureType::fontAD)]) return false;

    store[int_(enumTextureType::fontGameover)] =
        sdl->MakeTexture(enumGameFonts::gameover,
        gameTexturesPaths[int_(enumTextureType::fontGameover)]);
    if (!store[int_(enumTextureType::fontGameover)]) return false;
    return true;
#undef int_
}

TextureStore::~TextureStore()
{
    if (store)
    {
        for (auto t = 0; t < storeLength; t++)
        {
            if (store[t])
            {
                delete store[t];
                store[t] = nullptr;
            }

        }
        delete[] store;
        store = nullptr;
    }
}

