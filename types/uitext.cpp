#include "uitext.h"

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
