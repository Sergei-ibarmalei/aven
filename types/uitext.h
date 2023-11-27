#pragma once

#include "texturestore.h"
#include "simpleobject.h"


//Класс для хранения объектов - текстур из текста по типу
//PAUSE, Press Q to exit.. etc


class UItext: public Init
{
    private:
    SimpleObject** uiTextVector = nullptr;
    Plot startPos[static_cast<int>(enumGameFonts::all)] {0, 0};

    void initStartsPos(const TextureStore* store);
    bool initUiTextVector(const TextureStore* store);

    public:
    UItext(const TextureStore* store);
    ~UItext();
    SimpleObject* operator[](const enumGameFonts gameFont);
};

