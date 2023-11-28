#include "texture.h"

Texture::Texture(SDL_Texture* t,
    Rect** rectsVector,
    const int rectsVectorLength,
    enumTextureType type)
{

    if (!t || !rectsVector || rectsVectorLength <= 0)
    {
        init.Negate(); return;
    }
    sdlTexture = t;
    mainRectsVector = rectsVector;
    mainRectsVectorLength = rectsVectorLength;

    initMainRectsVector(type);
}

//Текстура из текста
Texture::Texture(SDL_Texture* t,
    Rect** rectsVector,
    SDL_Surface* surface)
{
    if (!t || !rectsVector || !surface)
    {
        init.Negate(); return;
    }
    sdlTexture = t;
    mainRectsVector = rectsVector;
    mainRectsVectorLength = 1;
    initMainRectsVectorFonts(surface);

}

void initMainRectsVector_digits(Rect** digitsVectorMainRect)
{
    const int stepx{ 98 };
    const int rectW{ 98 };
    const int rectH{ 82 };
    for (int i = 0; i < static_cast<int>(enumDigitsPack::all); i++)
    {
        digitsVectorMainRect[i] =
            new Rect(i * stepx, 0, rectW, rectH);
    }
}

void Texture::initMainRectsVectorFonts(SDL_Surface* surface)
{
    mainRectsVector[0] =
        new Rect(0,0,surface->w, surface->h);
    SDL_FreeSurface(surface);
}

void Texture::initMainRectsVector(enumTextureType textureType)
{
#define int_ static_cast<int>

    // ������ �� ����� ShipsJson.json
    switch (textureType)
    {
        case enumTextureType::ships:
        {
            //hero main rect
            mainRectsVector[int_(enumShipKind::hero)] =
            new Rect(HERO_MAINRECTX, HERO_MAINRECTY,
                HERO_MAINRECTW, HERO_MAINRECTH);
            //part 1 alien 1
            mainRectsVector[int_(enumShipKind::alien_one)] =
            new Rect(ALIENONE_MAINRECTX, ALIENONE_MAINRECTY,
                ALIENONE_MAINRECTW, ALIENONE_MAINRECTH);
            //part 1 alien 2
            mainRectsVector[int_(enumShipKind::alien_two)] =
            new Rect(ALIENTWO_MAINRECTX, ALIENTWO_MAINRECTY,
                ALIENTWO_MAINRECTW, ALIENTWO_MAINRECTH);
            //part 1 alien silent blue
            mainRectsVector[int_(enumShipKind::alien_silent_blue)] =
            new Rect(ALIENSILENTBLUE_MAINRECTX, ALIENSILENTBLUE_MAINRECTY,
                ALIENSILENTBLUE_MAINRECTW, ALIENSILENTBLUE_MAINRECTH);
            //part 1 alien silent brown
            mainRectsVector[int_(enumShipKind::alien_silent_brown)] =
            new Rect(ALIENSILENTBROWN_MAINRECTX, ALIENSILENTBROWN_MAINRECTY,
                ALIENSILENTBROWN_MAINRECTW, ALIENSILENTBROWN_MAINRECTW);
            break;
        }
        case enumTextureType::gameFon:
        {
            mainRectsVector[int_(enumFon::gameFon)] =
            new Rect(GAMEFON_MAINRECTX, GAMEFON_MAINRECTY,
                GAMEFON_MAINRECTW, GAMEFON_MAINRECTH);
            break;
        }

        case enumTextureType::digitsPack:
        {
            initMainRectsVector_digits(mainRectsVector);
            break;
        }

        case enumTextureType::shlemsPack:
        {
            mainRectsVector[int_(enumShlemsPack::liveShlem)] =
            new Rect(LIVESHLEM_MAINRECTX, LIVESHLEM_MAINRECTY,
                LIVESHLEM_MAINRECTW, LIVESHLEM_MAINRECTH);
            mainRectsVector[int_(enumShlemsPack::deadShlem)] =
            new Rect(DEADSHLEM_MAINRECTX, DEADSHLEM_MAINRECTY,
                DEADSHLEM_MAINRECTW, DEADSHLEM_MAINRECTH);
            break;
        }

        case enumTextureType::lasersPack:
        {
            mainRectsVector[int_(enumLasers::blue)] =
            new Rect(BLUELASER_MAINRECTX, BLUELASER_MAINRECTY,
                BLUELASER_MAINRECTW, BLUELASER_MAINRECTH);
            mainRectsVector[int_(enumLasers::red)] =
            new Rect(REDLASER_MAINRECTX, REDLASER_MAINRECTY,
                REDLASER_MAINRECTW, REDLASER_MAINRECTH);
            mainRectsVector[int_(enumLasers::yellow)] =
            new Rect(YELLOWLASER_MAINRECTX, YELLOWLASER_MAINRECTY,
                YELLOWLASER_MAINRECTW, YELLOWLASER_MAINRECTH);
            break;
        }

        case enumTextureType::cartoonBlow:
        {
            mainRectsVector[int_(enumCartoonBloowFrames::first)] =
            new Rect(BLOWFIRST_MAINRECTX, BLOWFIRST_MAINRECTY,
                BLOWFIRST_MAINRECTW, BLOWFIRST_MAINRECTH);
            mainRectsVector[int_(enumCartoonBloowFrames::second)] =
            new Rect(BLOWSECOND_MAINRECTX, BLOWSECOND_MAINRECTY,
                BLOWSECOND_MAINRECTW, BLOWSECOND_MAINRECTH);
            mainRectsVector[int_(enumCartoonBloowFrames::third)] =
            new Rect(BLOWTHIRD_MAINRECTX, BLOWTHIRD_MAINRECTY,
                BLOWTHIRD_MAINRECTW, BLOWTHIRD_MAINRECTH);
            mainRectsVector[int_(enumCartoonBloowFrames::fourth)] =
            new Rect(BLOWFOURTH_MAINRECTX, BLOWFOURTH_MAINRECTY,
                BLOWFOURTH_MAINRECTW, BLOWFOURTH_MAINRECTH);
            mainRectsVector[int_(enumCartoonBloowFrames::fifth)] =
            new Rect(BLOWFIFTH_MAINRECTX, BLOWFIFTH_MAINRECTY,
                BLOWFIFTH_MAINRECTW, BLOWFIFTH_MAINRECTH);
            mainRectsVector[int_(enumCartoonBloowFrames::sixth)] =
            new Rect(BLOWSIXTH_MAINRECTX, BLOWSIXTH_MAINRECTY,
                BLOWSIXTH_MAINRECTW, BLOWSIXTH_MAINRECTH);
            mainRectsVector[int_(enumCartoonBloowFrames::seventh)] =
            new Rect(BLOWSEVENTH_MAINRECTX, BLOWSEVENTH_MAINRECTY,
                BLOWSEVENTH_MAINRECTW, BLOWSEVENTH_MAINRECTH);
            break;
        }
        case enumTextureType::mainmenuText:
        {
            mainRectsVector[int_(enumTextingOrder::black_newgame)] =
                new Rect(BLACKNEWGAME_MAINRECTX, BLACKNEWGAME_MAINRECTY,
                    BLACKNEWGAME_MAINRECTW, BLACKNEWGAME_MAINRECTH);
            mainRectsVector[int_(enumTextingOrder::black_rules)] =
                new Rect(BLACKRULES_MAINRECTX, BLACKRULES_MAINRECTY,
                    BLACKRULES_MAINRECTW, BLACKRULES_MAINRECTH);
            mainRectsVector[int_(enumTextingOrder::black_exit)] =
                new Rect(BLACKEXIT_MAINRECTX, BLACKEXIT_MAINRECTY,
                    BLACKEXIT_MAINRECTW, BLACKEXIT_MAINRECTH);
            mainRectsVector[int_(enumTextingOrder::red_newgame)] =
                new Rect(REDNEWGAME_MAINRECTX, REDNEWGAME_MAINRECTY,
                    REDNEWGAME_MAINRECTW, REDNEWGAME_MAINRECTH);
            mainRectsVector[int_(enumTextingOrder::red_rules)] =
                new Rect(REDRULES_MAINRECTX, REDRULES_MAINRECTY,
                    REDRULES_MAINRECTW, REDRULES_MAINRECTH);
            mainRectsVector[int_(enumTextingOrder::red_exit)] =
                new Rect(REDEXIT_MAINRECTX, REDEXIT_MAINRECTY,
                    REDEXIT_MAINRECTW, REDEXIT_MAINRECTH);
            break;
        }

        default: {init.Negate(); }

    }
#undef int_
}




Rect* Texture::operator[](const int index) const
{
    if (index < 0 || index >= mainRectsVectorLength)
        return mainRectsVector[0];
    return mainRectsVector[index];
}

Texture::~Texture()
{
    if (sdlTexture)
        SDL_DestroyTexture(sdlTexture);
    sdlTexture = nullptr;



    if (mainRectsVector)
    {
        for (auto i = 0; i < mainRectsVectorLength; i++)
        {
            delete mainRectsVector[i];
            mainRectsVector[i] = nullptr;
        }
    }
    delete[] mainRectsVector;
    mainRectsVector = nullptr;
}