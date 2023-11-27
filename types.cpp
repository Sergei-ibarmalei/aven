
#include "types.h"

std::ostream& operator<<(std::ostream& os, const Rect& r)
{
    os << "[x: " << r.x << ", y: " << r.y << ", w: " << r.w <<
        ", h: " << r.h << "]\n";
    return os;
}


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

Texture::Texture(SDL_Texture* t,
    Rect** rectsVector,
    const int rectsVectorLength,
    enumTextureType type)
{

    if (!t || !rectsVector || rectsVectorLength <= 0)
    {
        init_ok = false;
        return;
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
        init_ok = false;
        return;
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

        default: {init_ok = false; }

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


SimpleObject::SimpleObject(const Texture* t,
    const Plot& start,
    const int objectMainRectNomber)
{
    if (!t)
    {
        init_ok = false; return;
    }
    this->objectMainRect = new Rect{ 0, 0, 0, 0 };
    this->startPos = start;
    if (!setMainRectFromTexture(t->operator[](objectMainRectNomber)))
    {
        init_ok = false; return;
    }
    initObjectMainRect();
}

bool SimpleObject::setMainRectFromTexture(Rect* mainRectFromTexture_)
{
    if (!mainRectFromTexture_) return false;
    this->mainRectFromTexture = mainRectFromTexture_;
    return true;
}

SimpleObject::~SimpleObject()
{
    mainRectFromTexture = nullptr;
    delete objectMainRect;
    objectMainRect = nullptr;

}



void SimpleObject::initObjectMainRect()
{
    this->objectMainRect->x = startPos.x;
    this->objectMainRect->y = startPos.y;
    this->objectMainRect->w = this->mainRectFromTexture->w;
    this->objectMainRect->h = this->mainRectFromTexture->h;
    if (*this->objectMainRect == awindow)
        this->objectStatus = enumObjectStatus::isOnScreen;

    //init Center
    this->objectCenter.x = this->objectMainRect->x +
        (this->mainRectFromTexture->w >> 1);
    this->objectCenter.y = this->objectMainRect->y +
        (this->mainRectFromTexture->h >> 1);
}

void SimpleObject::recomputeObjectMainRect()
{
    if (this->objectMainRect)
    {
        this->objectMainRect->x += this->objectVelocity.x;
        this->objectMainRect->y += this->objectVelocity.y;

        this->objectCenter.x = this->objectMainRect->x + 
            (this->objectMainRect->w >> 1);
        this->objectCenter.y = this->objectMainRect->y +
            (this->objectMainRect->h >> 1);


    }

}

std::ostream& operator<<(std::ostream& os, const SimpleObject& o)
{
    os << "Object main rect: [x: " << o.objectMainRect->x <<
        ", y: " << o.objectMainRect->y <<
        ", w: " << o.objectMainRect->w <<
        ", h: " << o.objectMainRect->h << "]\n" <<
        "Object texture main rect: [x: " << o.mainRectFromTexture->x <<
        ", y: " << o.mainRectFromTexture->y <<
        ", w: " << o.mainRectFromTexture->w <<
        ", h: " << o.mainRectFromTexture->h << "]\n";
    return os;
}

bool SimpleObject::InEshelon(const Eshelon& e)
{
    return (objectCenter.y > e.ceiling && objectCenter.y < e.floor);
}



ComplexObject::ComplexObject(const Texture* t,
    const Plot& start,
    const int objectMainRectNomber) :
    SimpleObject(t, start, objectMainRectNomber)
{
    if (SimpleObject::init_ok == false) return;
}





void ComplexObject::recomputeCollideVector()
{
    if (!this->objectCollideVector) return;
    for (auto r = 0; r < this->objectCollideVectorLength; r++)
    {
        objectCollideVector[r]->x += this->objectVelocity.x;
        objectCollideVector[r]->y += this->objectVelocity.y;
    }
}

bool ComplexObject::operator==(const ComplexObject& o)
{
    if (!o.objectCollideVector || (o.objectCollideVectorLength <= 0))
        return false;

    if (*this->objectMainRect == *o.objectMainRect)
    {
        for (int r = 0; r < this->objectCollideVectorLength; r++)
        {
            for (int _or = 0; _or < o.objectCollideVectorLength; _or++)
            {
                if (*this->objectCollideVector[r] ==
                    *o.objectCollideVector[_or])
                    return true;
            }
        }
    }
    return false;
}

bool ComplexObject::operator==(const SimpleObject& s)
{
    if (!s.ObjectMainRect()) return false;
    return *this->objectMainRect == *s.ObjectMainRect();
}

ComplexObject::~ComplexObject()
{
    if (objectCollideVector && objectCollideVectorLength > 0)
    {
        for (auto r = 0; r < objectCollideVectorLength; r++)
        {
            delete objectCollideVector[r];
            objectCollideVector[r] = nullptr;
        }
        delete[] objectCollideVector;
        objectCollideVector = nullptr;
    }
}


Laser::Laser(enumLaserKind laserKind,
    const Texture* t,
    const Plot& start,
    const int objectMainRectNomber) :
    SimpleObject(t, start, objectMainRectNomber)
{
    this->kind = laserKind;
    switch (laserKind)
    {
        case enumLaserKind::heroLaser:
        {
            this->objectVelocity.x = HEROLASER_VEL;
            break;
        }
        case enumLaserKind::alienLaser:
        {
            this->objectVelocity.x = ALIENLASER_VEL;
            break;
        }
        default: {}
    }
}

void Laser::Move()
{
    if (this->ObjectStatus() != enumObjectStatus::isOnScreen) return;

    switch (kind)
    {
        case enumLaserKind::heroLaser:
        {
            this->objectMainRect->x += this->objectVelocity.x;
            break;
        }
        case enumLaserKind::alienLaser:
        {
            this->objectMainRect->x -= this->objectVelocity.x;
            break;
        }
        default: {}
    }
    if (*this->objectMainRect == awindow) this->objectStatus =
        enumObjectStatus::isOnScreen;
    else this->objectStatus = enumObjectStatus::isCrashed;

}

bool Laser::operator==(const ComplexObject& o)
{
    int lengthCollideVector = o.CmplObjectCollideVectorLength();
    Rect** objectCollideVector = o.ObjectCollideVector();
    if (*this->objectMainRect == *o.ObjectMainRect())
    {
        for (auto r = 0; r < lengthCollideVector; r++)
        {

            if (*this->objectMainRect == *objectCollideVector[r]) return true;
        }
    }
    return false;
}

bool Laser::operator==(const Ship& o)
{
    int lengthCollideVector = o.CmplObjectCollideVectorLength();
    Rect** objectCollideVector = o.ObjectCollideVector();
    if (*this->objectMainRect == *o.ObjectMainRect())
    {
        for (auto r = 0; r < lengthCollideVector; r++)
        {

            if (*this->objectMainRect == *objectCollideVector[r]) return true;
        }
    }
    return false;
}

std::ostream& operator<<(std::ostream& os, const Laser& l)
{
    os << "new laser at: [" << l.startPos.x << ", " << l.startPos.y <<
        "]\n";
    return os;
}



ScoreBase::ScoreBase(const int objectScore)
{
    score = objectScore;
}


Ship::Ship(enumShipKind shipKind, const Texture* t,
    const Plot& start,
    const int objectMainRectNomber,
    const int objectScore) :
    ComplexObject(t, start, objectMainRectNomber), ScoreBase(objectScore)
{
    if (SimpleObject::init_ok == false) return;
    this->laserStartPos = setLaserStartPos(shipKind);
    initCollideVector(shipKind);

}

void Ship::initCollideVector(enumShipKind shipKind)
{
    switch (shipKind)
    {
        case enumShipKind::hero:
        {
            this->objectCollideVectorLength = HEROCOLLIDEVECTORLENGTH;
            this->objectCollideVector =
                new Rect * [this->objectCollideVectorLength];
            break;
        }
        case enumShipKind::alien_one:
        {
            this->objectCollideVectorLength = ALIENONECOLLIDEVECTORLENGTH;
            this->objectCollideVector =
                new Rect * [this->objectCollideVectorLength];
            break;
        }
        default: {}
    }
}

Plot* Ship::setLaserStartPos(enumShipKind shipKind)
{
    switch (shipKind)
    {
        case enumShipKind::hero:
        {
            return new Plot{ this->objectMainRect->x +
                this->objectMainRect->w + LASERSHIFT,
                this->objectMainRect->y + HEROLASER_YPOS };
            break;
        }
        case enumShipKind::alien_one:
        {
            return new Plot{ this->objectMainRect->x -
                LASERSHIFT - ALIENONELASER_W,
                this->objectMainRect->y + 
            ALIENONELASERGUN_Y - (ALIENONELASER_H>>1)  };
            break;
        }
        case enumShipKind::alien_two:
        {
            return new Plot{ this->objectMainRect->x -
                LASERSHIFT,
                this->objectMainRect->y +
            (this->objectMainRect->h >> 1) };
            break;
        }
        case enumShipKind::alien_silent_blue:
        case enumShipKind::alien_silent_brown:
        {
            return nullptr;
            break;
        }
        default: return nullptr;

    }
}


void Ship::recompute()
{
    if (this->objectStatus == enumObjectStatus::isCrashed) return;
    if (this->laserStartPos)
    {
        this->laserStartPos->x += this->objectVelocity.x;
        this->laserStartPos->y += this->objectVelocity.y;
    }
    ComplexObject::recomputeCollideVector();
    SimpleObject::recomputeObjectMainRect();

    if (this->objectStatus == enumObjectStatus::isOnScreen) return;

    if (*this->objectMainRect == awindow)
        this->objectStatus = enumObjectStatus::isOnScreen;

}

bool Ship::InEshelon(const Eshelon& e)
{
    return (this->objectCenter.y > e.ceiling && this->objectCenter.y < e.floor);
}

Ship::~Ship()
{
    if (this->laserStartPos)
    {
        delete this->laserStartPos;
        this->laserStartPos = nullptr;
    }
}




static Rect heroCollidingVector[HEROCOLLIDEVECTORLENGTH] =
{
    {184, 27, 4, 22},
    {174, 21, 4, 4},
    {149, 14, 4, 4},
    {124, 7, 4, 4},
    {105, 0, 4, 4},
    {90, 50, 4, 4},
    {83, 53, 4, 4},
    {77, 60, 4, 4}
};

Hero::Hero(const Texture* t, const Plot& start) :
    Ship(enumShipKind::hero, t, start, static_cast<int>(enumShipKind::hero))
{

    if (Ship::init_ok == false) return;
    fillCollide();
    heroStopIntro = MAINWINDOW_H >> 2;
}



bool Hero::crossedUp()
{
    return (this->objectMainRect->y + this->objectVelocity.y) <=
        awindow.y;
}

bool Hero::crossedDown()
{
    return (this->objectMainRect->y + this->objectMainRect->h +
        this->objectVelocity.y) >= awindow.y + awindow.h;
}

bool Hero::crossedRight()
{
    return (this->objectMainRect->x + this->objectMainRect->w +
        this->objectVelocity.x) >= awindow.x + awindow.w;
}


bool Hero::crossedLeft()
{
    return (this->objectMainRect->x + this->objectVelocity.x) <=
        awindow.x;
}

void Hero::fillCollide()
{
    for (auto r = 0; r < HEROCOLLIDEVECTORLENGTH; r++)
    {
        this->objectCollideVector[r] = new Rect{0, 0, 0, 0};
    }


}

void Hero::fillCollideAfterStart()
{
    for (auto r = 0; r < HEROCOLLIDEVECTORLENGTH; r++)
    {
        this->objectCollideVector[r]->x =
            this->objectMainRect->x + heroCollidingVector[r].x;
        this->objectCollideVector[r]->y =
            this->objectMainRect->y + heroCollidingVector[r].y;
        this->objectCollideVector[r]->w = heroCollidingVector[r].w;
        this->objectCollideVector[r]->h = heroCollidingVector[r].h;
    }


}

void Hero::Move()
{
    if (crossedUp())   return;
    if (crossedDown())  return;
    if (crossedLeft())  return;
    if (crossedRight()) return;
    Ship::recompute();

    //Перерасчет эшелона героя
    heroEshelon.ceiling = objectMainRect->y - HEROESHELONTOCEILING;
    heroEshelon.floor = objectMainRect->y + objectMainRect->h +
        HEROESHELONTOFLOOR;
}

void Hero::MoveIntro(GameState* gameState)
{
    if (gameState->heroIntro == false) return;
    this->objectMainRect->x += HEROINTRO_VEL;
    recomputeIntro();
    if (this->objectMainRect->x >= this->heroStopIntro)
    {
        gameState->heroIntro = false;
        this->objectVelocity.x = 0;
        fillCollideAfterStart();
        laserStartPos = Ship::setLaserStartPos(enumShipKind::hero);
    }
}

void Hero::recomputeIntro()
{

    SimpleObject::recomputeObjectMainRect();

    if (this->objectStatus == enumObjectStatus::isOnScreen) return;

    if (*this->objectMainRect == awindow)
        this->objectStatus = enumObjectStatus::isOnScreen;
}







void Hero::MoveLeft(const int velocity_x)
{
    this->objectVelocity.x -= velocity_x;
    this->Move();
}

void Hero::MoveRight(const int velocity_x)
{
    this->objectVelocity.x += velocity_x;
    this->Move();
}

void Hero::MoveUp(const int velocity_y)
{
    this->objectVelocity.y -= velocity_y;
    this->Move();
}

void Hero::MoveDown(const int velocity_y)
{
    this->objectVelocity.y += velocity_y;
    this->Move();
}

void Hero::Stop()
{
    this->objectVelocity.x = this->objectVelocity.y = 0;
}

bool Hero::operator==(const Ship& ship)
{
    return *Ship::objectMainRect == *ship.GetShipMainRect();
}



static Rect alienCollidingVector[ALIENONECOLLIDEVECTORLENGTH] =
{
    {0, 29, 4, 20},
    {10, 23, 4, 4},
    {24, 16, 4, 4},
    {33, 9, 4, 4},
    {46, 4, 4, 4},
    {84, 0, 4, 4},
    {15, 52, 4, 4}
};


void AlienStrightShooting::CountStepToShoot(enumObjectStatus status,
                                     const int velocity)
{
    if (mayShoot) return;
    if (status != enumObjectStatus::isOnScreen) return;
    currentStep -= velocity;
    if (currentStep >= stepsToShoot)
    {
        mayShoot = true;
    }
}

void AlienStrightShooting::CantShoot()
{
    mayShoot = false;
    currentStep = 0;
}



Alien_one::Alien_one(const Texture* t,
                     const Plot& start,
                     const int objectScore) :
    Ship(enumShipKind::alien_one,
                       t,
                       start,
                       static_cast<int>(enumShipKind::alien_one),
                       objectScore)
{
    if (Ship::init_ok == false) return;
    fillCollide();
    this->objectVelocity.x = ALIENONEFLEET_VEL;
    alienShooting = new AlienStrightShooting {ALIENONE_STEPTOSHOOT};
}

void Alien_one::fillCollide()
{
    for (auto r = 0; r < ALIENONECOLLIDEVECTORLENGTH; r++)
    {
        this->objectCollideVector[r] =
            new Rect{ this->objectMainRect->x + alienCollidingVector[r].x,
                     this->objectMainRect->y + alienCollidingVector[r].y,
                     alienCollidingVector[r].w,
                     alienCollidingVector[r].h };
    }

}


void Alien_one::Move()
{
    if (this->ObjectStatus() == enumObjectStatus::isCrashed) return;

    Ship::recompute();

    //отсчитываем шаги для выполнения выстрела
    this->alienShooting->CountStepToShoot(this->ObjectStatus(),
        this->objectVelocity.x);

    if (this->objectStatus == enumObjectStatus::isOnScreen &&
        !(*this->objectMainRect == awindow))
    {
        this->objectStatus = enumObjectStatus::isCrashed;
        return;
    }

}

Alien_one::~Alien_one()
{
    delete alienShooting;
    alienShooting = nullptr;
}


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


HUD_lives::HUD_lives(const Texture* t)
{
#define int_ static_cast<int>
    if (!t)
    {
        init_ok = false; return;
    }
    setCenters();
    setLivesThree(centers, t);
    setLivesTwo(centers, t);
    setLivesOne(centers, t);
    setLivesZero(centers, t);

#undef int_
}

void HUD_lives::Reinit()
{
    heroLives = 3;
}

void HUD_lives::setLivesThree(const Plot* centers, const Texture* t)
{
#define int_ static_cast<int>
#define LEFT_POSITION static_cast<int>(enumHudLivesPosition::left)
#define CENTER_POSITION static_cast<int>(enumHudLivesPosition::center)
#define RIGHT_POSITION  static_cast<int>(enumHudLivesPosition::right)
#define DEAD_TEXTURE static_cast<int>(enumShlemsPack::deadShlem)
#define LIVE_TEXTURE static_cast<int>(enumShlemsPack::liveShlem)

    lives_three[LEFT_POSITION].x =
        centers[LEFT_POSITION].x - live_half.x;
    lives_three[LEFT_POSITION].y =
        centers[LEFT_POSITION].y - live_half.y;
    lives_three[LEFT_POSITION].w =
        t->operator[](LIVE_TEXTURE)->w;
    lives_three[LEFT_POSITION].h =
        t->operator[](LIVE_TEXTURE)->h;

    lives_three[CENTER_POSITION].x =
        centers[CENTER_POSITION].x - live_half.x;
    lives_three[CENTER_POSITION].y =
        centers[CENTER_POSITION].y - live_half.y;
    lives_three[CENTER_POSITION].w =
        t->operator[](LIVE_TEXTURE)->w;
    lives_three[CENTER_POSITION].h =
        t->operator[](LIVE_TEXTURE)->h;

    lives_three[RIGHT_POSITION].x =
        centers[RIGHT_POSITION].x - live_half.x;
    lives_three[RIGHT_POSITION].y =
        centers[RIGHT_POSITION].y - live_half.y;
    lives_three[RIGHT_POSITION].w =
        t->operator[](LIVE_TEXTURE)->w;
    lives_three[RIGHT_POSITION].h =
        t->operator[](LIVE_TEXTURE)->h;

#undef int_
#undef LEFT_POSITION
#undef CENTER_POSITION
#undef RIGHT_POSITION
#undef DEAD_TEXTURE
#undef LIVE_TEXTURE
}

void HUD_lives::setLivesTwo(const Plot* centers, const Texture* t)
{

#define LEFT_POSITION static_cast<int>(enumHudLivesPosition::left)
#define CENTER_POSITION static_cast<int>(enumHudLivesPosition::center)
#define RIGHT_POSITION  static_cast<int>(enumHudLivesPosition::right)
#define DEAD_TEXTURE static_cast<int>(enumShlemsPack::deadShlem)
#define LIVE_TEXTURE static_cast<int>(enumShlemsPack::liveShlem)
#define int_ static_cast<int>

    lives_two[LEFT_POSITION].x =
        centers[LEFT_POSITION].x - live_half.x;
    lives_two[LEFT_POSITION].y =
        centers[LEFT_POSITION].y - live_half.y;
    lives_two[LEFT_POSITION].w =
        t->operator[](LIVE_TEXTURE)->w;
    lives_two[LEFT_POSITION].h =
        t->operator[](LIVE_TEXTURE)->h;

    lives_two[CENTER_POSITION].x =
        centers[CENTER_POSITION].x - live_half.x;
    lives_two[CENTER_POSITION].y =
        centers[CENTER_POSITION].y - live_half.y;
    lives_two[CENTER_POSITION].w =
        t->operator[](LIVE_TEXTURE)->w;
    lives_two[CENTER_POSITION].h =
        t->operator[](LIVE_TEXTURE)->h;

    lives_two[RIGHT_POSITION].x =
        centers[RIGHT_POSITION].x - live_half.x;
    lives_two[RIGHT_POSITION].y =
        centers[RIGHT_POSITION].y - live_half.y;
    lives_two[RIGHT_POSITION].w =
        t->operator[](DEAD_TEXTURE)->w;
    lives_two[RIGHT_POSITION].h =
        t->operator[](DEAD_TEXTURE)->h;

#undef int_
#undef LEFT_POSITION
#undef CENTER_POSITION
#undef RIGHT_POSITION
#undef DEAD_TEXTURE
#undef LIVE_TEXTURE
}

void HUD_lives::setLivesOne(const Plot* centers, const Texture* t)
{
#define int_ static_cast<int>
#define int_ static_cast<int>
#define LEFT_POSITION static_cast<int>(enumHudLivesPosition::left)
#define CENTER_POSITION static_cast<int>(enumHudLivesPosition::center)
#define RIGHT_POSITION  static_cast<int>(enumHudLivesPosition::right)
#define DEAD_TEXTURE static_cast<int>(enumShlemsPack::deadShlem)
#define LIVE_TEXTURE static_cast<int>(enumShlemsPack::liveShlem)

    lives_one[LEFT_POSITION].x =
        centers[LEFT_POSITION].x - live_half.x;
    lives_one[LEFT_POSITION].y =
        centers[LEFT_POSITION].y - live_half.y;
    lives_one[LEFT_POSITION].w =
        t->operator[](LIVE_TEXTURE)->w;
    lives_one[LEFT_POSITION].h =
        t->operator[](LIVE_TEXTURE)->h;

    lives_one[CENTER_POSITION].x =
        centers[CENTER_POSITION].x - live_half.x;
    lives_one[CENTER_POSITION].y =
        centers[CENTER_POSITION].y - live_half.y;
    lives_one[CENTER_POSITION].w =
        t->operator[](DEAD_TEXTURE)->w;
    lives_one[CENTER_POSITION].h =
        t->operator[](DEAD_TEXTURE)->h;

    lives_one[RIGHT_POSITION].x =
        centers[RIGHT_POSITION].x - live_half.x;
    lives_one[RIGHT_POSITION].y =
        centers[RIGHT_POSITION].y - live_half.y;
    lives_one[RIGHT_POSITION].w =
        t->operator[](DEAD_TEXTURE)->w;
    lives_one[RIGHT_POSITION].h =
        t->operator[](DEAD_TEXTURE)->h;

#undef int_
#undef LEFT_POSITION
#undef CENTER_POSITION
#undef RIGHT_POSITION
#undef DEAD_TEXTURE
#undef LIVE_TEXTURE
}

void HUD_lives::setLivesZero(const Plot* centers, const Texture* t)
{

#define int_ static_cast<int>
#define LEFT_POSITION static_cast<int>(enumHudLivesPosition::left)
#define CENTER_POSITION static_cast<int>(enumHudLivesPosition::center)
#define RIGHT_POSITION  static_cast<int>(enumHudLivesPosition::right)
#define DEAD_TEXTURE static_cast<int>(enumShlemsPack::deadShlem)



    lives_zero[LEFT_POSITION].x =
        centers[LEFT_POSITION].x - live_half.x;
    lives_zero[LEFT_POSITION].y =
        centers[LEFT_POSITION].y - live_half.y;
    lives_zero[LEFT_POSITION].w =
        t->operator[](DEAD_TEXTURE)->w;
    lives_zero[LEFT_POSITION].h =
        t->operator[](DEAD_TEXTURE)->h;

    lives_zero[CENTER_POSITION].x =
        centers[CENTER_POSITION].x - live_half.x;
    lives_zero[CENTER_POSITION].y =
        centers[CENTER_POSITION].y - live_half.y;
    lives_zero[CENTER_POSITION].w =
        t->operator[](DEAD_TEXTURE)->w;
    lives_zero[CENTER_POSITION].h =
        t->operator[](DEAD_TEXTURE)->h;

    lives_zero[RIGHT_POSITION].x =
        centers[RIGHT_POSITION].x - live_half.x;
    lives_zero[RIGHT_POSITION].y =
        centers[RIGHT_POSITION].y - live_half.y;
    lives_zero[RIGHT_POSITION].w =
        t->operator[](DEAD_TEXTURE)->w;
    lives_zero[RIGHT_POSITION].h =
        t->operator[](DEAD_TEXTURE)->h;


#undef LEFT_POSITION
#undef CENTER_POSITION
#undef RIGHT_POSITION
#undef DEAD_TEXTURE
#undef int_


}




void HUD_lives::setCenters()
{
    const int stepx{ 187 };
    const int y{ 61 };


    centers[static_cast<int>(enumHudLivesPosition::left)].x = stepx;
    centers[static_cast<int>(enumHudLivesPosition::left)].y = y;
    centers[static_cast<int>(enumHudLivesPosition::center)].x = 2 * stepx;
    centers[static_cast<int>(enumHudLivesPosition::center)].y = y;
    centers[static_cast<int>(enumHudLivesPosition::right)].x = 3 * stepx;
    centers[static_cast<int>(enumHudLivesPosition::right)].y = y;
}


HUD_score::HUD_score()
{
    initHudScoreMainRects();
}

void HUD_score::ResetGameScore()
{
    gameScore = 0;
    SetScore(0);
}





void HUD_score::initHudScoreMainRects()
{
    Plot upLeftCorner;
    const int SCORES_W{ 490 };
    const int digit_w{ 98 };
    const int digit_h{ 82 };
    upLeftCorner.x = HUD_SCORE_CENTER.x - (SCORES_W >> 1);
    upLeftCorner.y = HUD_SCORE_CENTER.y - (digit_h >> 1);

    for (auto s = 0; s < HUD_SCORE_LENGTH; s++)
    {
        hudScoreMainRects[s].x = upLeftCorner.x + (s * digit_w);
        hudScoreMainRects[s].y = upLeftCorner.y;
        hudScoreMainRects[s].w = digit_w;
        hudScoreMainRects[s].h = digit_h;
    }

}

void HUD_score::SetScore(int score)
{
    this->gameScore += score;
    int tmpScore = this->gameScore;
    for (auto i = 0; i < HUD_SCORE_LENGTH; i++)
    {
        hudScore[i] = tmpScore / delimeter[i];
        tmpScore %= delimeter[i];

    }
}



void Sky::moving(std::mt19937& mt, Plot* arr, const int length, const int vel)
{
    for (auto s = 0; s < length; s++)
    {
        arr[s].x -= vel;
        if (arr[s].x < awindow.x)
        {
            arr[s].x = awindow.w;
            std::uniform_int_distribution<int> y{ ceiling, floor };
            arr[s].y = y(mt);
        }
    }
}

void Sky::Move(std::mt19937& mt)
{
    moving(mt, fast, FASTSTARARRLENGTH, FASTSTARVELOCITY);
    moving(mt, slow, SLOWSTARARRLENGTH, SLOWSTARVELOCITY);
}






FleetBase::FleetBase(const int size)
{
    if (size <= 0)
    {
        init_ok = false; return;
    }
    this->currentFleetSize = size;

}


FleetBase::~FleetBase()
{
    for (auto& ship : fleetVector)
    {
        delete ship;
        ship = nullptr;
    }

}





Fleet_AlienOne::Fleet_AlienOne(std::mt19937& mt,
    const TextureStore* store,
    enumFleetKind kind,
    const int size): FleetBase(size)
{
    switch (kind)
    {
        case enumFleetKind::alienOneFleet:
        {
            init_ok =
                makeFleetOne(mt, store->operator[](enumTextureType::ships));
            break;
        }
        default: {}
    }
}


bool Fleet_AlienOne::makeFleetOne(std::mt19937& mt, const Texture* t)
{
    int startPoint{ MAINWINDOW_W };
    int step{ 550 };
    int sideShift{ 100 };
    int alienHeight{ ALIENONE_MAINRECTH };
    int ceiling{ awindow.y + sideShift };
    int floor{ awindow.h - sideShift - alienHeight };
    Plot start{ 0, 0 };

    std::uniform_int_distribution<int> y{ ceiling, floor };

    for (auto a = 0; a < this->currentFleetSize; a++)
    {
        start.x = startPoint + step * a;
        start.y = y(mt);
        auto ship = new Alien_one(t, start, ALIENONESCORE);
        if (ship->Init_ok() == false) return false;
        this->fleetVector.push_back(ship);


    }


    return true;
}


CartoonObject::CartoonObject(const Plot& center, const Texture* t,
                            const int nomberFrames)
{
    if (!t || nomberFrames <= 0)
    {
        init_ok = false; return;
    }
    this->allFrames = nomberFrames;
    initRects(t, center);

}

void CartoonObject::initRects(const Texture* t, const Plot& center)
{
    for (auto frame = 0; frame < allFrames; frame++)
    {
        this->textureMainRects.push_back(t->operator[](frame));
        this->objectMainRects.push_back(new Rect{
            center.x - ((t->operator[](frame)->w)>>1),
            center.y - ((t->operator[](frame)->h)>>1),
            t->operator[](frame)->w,
            t->operator[](frame)->h });
    }
}

CartoonObject::~CartoonObject()
{
    for (SDL_Rect* r : textureMainRects)
    {
        delete r;
        r = nullptr;
    }
    for (SDL_Rect* r : objectMainRects)
    {
        delete r;
        r = nullptr;
    }
}

void CartoonObject::Tick()
{
    this->currentFrame += 1;
    if (this->currentFrame > this->allFrames)
        this->objectStatus = enumObjectStatus::isCrashed;
}



MainMenu::MainMenu(const Texture* t)
{
    if (!t) { init_ok = false; return; }
    initStartPoints(t);
    initVector(t);
}

void MainMenu::initStartPoints(const Texture* t)
{
    const int step{(MAINWINDOW_H >> 2)};
    const int centerX{(MAINWINDOW_W >> 1) };

    for (auto i = static_cast<int>(enumTextingOrder::black_newgame);
        i < static_cast<int>(enumTextingOrder::red_newgame); i++)
    {
        startPoints.push_back({ centerX - (t->operator[](i)->w >> 1),
            ((i * step)+step) - (t->operator[](i)->h >> 1) });
    }

}

void MainMenu::initVector(const Texture* t)
{

#define int_ static_cast<int>
    mm_vector.push_back(new TextObject(t,
        startPoints[int_(enumTextingOrder::black_newgame)],
        int_(enumTextingOrder::black_newgame)));
    mm_vector.push_back(new TextObject(t,
        startPoints[int_(enumTextingOrder::black_rules)],
        int_(enumTextingOrder::black_rules)));
    mm_vector.push_back(new TextObject(t,
        startPoints[int_(enumTextingOrder::black_exit)],
        int_(enumTextingOrder::black_exit)));

    mm_vector.push_back(new TextObject(t,
        startPoints[int_(enumTextingOrder::black_newgame)],
        int_(enumTextingOrder::red_newgame)));
    mm_vector.push_back(new TextObject(t,
        startPoints[int_(enumTextingOrder::black_rules)],
        int_(enumTextingOrder::red_rules)));
    mm_vector.push_back(new TextObject(t,
        startPoints[int_(enumTextingOrder::black_exit)],
        int_(enumTextingOrder::red_exit)));


#undef int_
}

void MainMenu::NextChoise()
{
    menuChoise += 1;
    if (menuChoise >= static_cast<int>(enumMainMenuChoise::all))
        menuChoise = static_cast<int>(enumMainMenuChoise::new_game);
}

void MainMenu::PrevChoise()
{
    menuChoise -= 1;
    if (menuChoise < static_cast<int>(enumMainMenuChoise::new_game))
        menuChoise = static_cast<int>(enumMainMenuChoise::exit);
}

MainMenu::~MainMenu()
{
    for (auto string_object : mm_vector)
    {
        delete string_object;
        string_object = nullptr;
    }
}

UItext::UItext(const TextureStore* store)
{
#define int_ static_cast<int>
    if (!store)
    {
        init_ok = false; return;
    }
    //Стартовые точки для текстур из текста
    initStartsPos(store);
    uiTextVector = new SimpleObject *
        [int_(enumGameFonts::all)] {nullptr};
    if (!initUiTextVector(store)) init_ok = false;
#undef int_
}

bool UItext::initUiTextVector(const TextureStore* store)
{
#define int_ static_cast<int>
    uiTextVector[int_(enumGameFonts::pause)] =
        new SimpleObject {store->operator[](enumTextureType::fontPause),
        startPos[int_(enumGameFonts::pause)]};
    if (uiTextVector[int_(enumGameFonts::pause)]->Init_ok() == false)
        return false;
    uiTextVector[int_(enumGameFonts::pressQ)] =
        new SimpleObject {store->operator[](enumTextureType::fontPressQ),
        startPos[int_(enumGameFonts::pressQ)]};
    if (uiTextVector[int_(enumGameFonts::pressQ)]->Init_ok() == false)
        return false;
    uiTextVector[int_(enumGameFonts::pressEsc)] =
        new SimpleObject {store->operator[](enumTextureType::fontPressEsc),
        startPos[int_(enumGameFonts::pressEsc)]};
    if (uiTextVector[int_(enumGameFonts::pressEsc)]->Init_ok() == false)
        return false;
    uiTextVector[int_(enumGameFonts::de)] =
        new SimpleObject {store->operator[](enumTextureType::fontDE),
        startPos[int_(enumGameFonts::de)]};
    if (uiTextVector[int(enumGameFonts::de)]->Init_ok() == false)
        return false;
    uiTextVector[int_(enumGameFonts::ad)] =
        new SimpleObject {store->operator[](enumTextureType::fontAD),
        startPos[int_(enumGameFonts::ad)]};
    if (uiTextVector[int_(enumGameFonts::ad)]->Init_ok() == false)
        return false;
    uiTextVector[int_(enumGameFonts::gameover)] =
        new SimpleObject {store->operator[](enumTextureType::fontGameover),
        startPos[int_(enumGameFonts::gameover)]};
    if (uiTextVector[int_(enumGameFonts::gameover)]->Init_ok() == false)
        return false;
    return true;

#undef int_
}

SimpleObject* UItext::operator[](const enumGameFonts gameFont)
{
    return uiTextVector[static_cast<int>(gameFont)];
}

UItext::~UItext()
{
    for (int t = 0; t < static_cast<int>(enumGameFonts::all); t++)
    {
        delete uiTextVector[t];
        uiTextVector[t] = nullptr;
    }
    delete[] uiTextVector;
    uiTextVector = nullptr;
}

void UItext::initStartsPos(const  TextureStore* store)
{
#define int_ static_cast<int>
    startPos[int_(enumGameFonts::pause)].x =
        (awindow.w >> 1) -
        (store->operator[](enumTextureType::fontPause)->operator[](0)->w >> 1);
    startPos[int_(enumGameFonts::pause)].y =
        (awindow.h >> 1) -
        (store->operator[](enumTextureType::fontPause)->operator[](0)->h >> 1);

    startPos[int_(enumGameFonts::gameover)].x =
        (awindow.w >> 1) -
        (store->operator[](enumTextureType::fontGameover)->
            operator[](0)->w >> 1);
    startPos[int_(enumGameFonts::gameover)].y =
        (awindow.h >> 1) -
        (store->operator[](enumTextureType::fontGameover)->
            operator[](0)->h >> 1);


    startPos[int_(enumGameFonts::pressQ)].x =
    (awindow.w >> 1) -
    (store->operator[](enumTextureType::fontPressQ)->operator[](0)->w >> 1);
    startPos[int_(enumGameFonts::pressQ)].y =
        awindow.h - 20 -
        store->operator[](enumTextureType::fontPressQ)->operator[](0)->h;

    startPos[int_(enumGameFonts::pressEsc)].x =
    (awindow.w >> 1) -
    (store->operator[](enumTextureType::fontPressEsc)->operator[](0)->w >> 1);
    startPos[int_(enumGameFonts::pressEsc)].y =
        awindow.h - 20 -
        store->operator[](enumTextureType::fontPressEsc)->operator[](0)->h;


    startPos[int_(enumGameFonts::de)].x =
        awindow.x - ACTIONWINDOW_SHIFT_X -
        store->operator[](enumTextureType::fontDE)->operator[](0)->w;
    startPos[int_(enumGameFonts::de)].y =
        (awindow.h >> 1) -
        (store->operator[](enumTextureType::fontDE)->operator[](0)->h >> 1);

    startPos[int_(enumGameFonts::ad)].x =
        awindow.w + ACTIONWINDOW_SHIFT_X;
    startPos[int_(enumGameFonts::ad)].y =
        (awindow.h >> 1) -
        (store->operator[](enumTextureType::fontAD)->operator[](0)->h >> 1);



#undef int_
}

TableCos::TableCos()
{
    const double rad = 3.14159265/180.0;
    vcos = new double[tableLength];
    for (int i = 0; i < tableLength; i++)
    {
        vcos[i] = cos(static_cast<double>(i) * rad);
    }
}

double TableCos::operator[](const int index)
{
    if (index < 0) return vcos[0];
    if (index > tableLength) return vcos[tableLength];
    return vcos[index];
}

TableCos::~TableCos()
{
    delete[] vcos;
    vcos = nullptr;
}

TableSin::TableSin()
{
    const double rad = 3.14159265/180.0;
    vsin = new double[tableLength];
    for (int i = 0; i < tableLength; i++)
    {
        vsin[i] = sin(static_cast<double>(i) * rad);
    }
}

double TableSin::operator[](const int index)
{
    if (index < 0) return vsin[0];
    if (index > tableLength) return vsin[tableLength];
    return vsin[index];
}

TableSin::~TableSin()
{
    delete[] vsin;
    vsin = nullptr;
}
