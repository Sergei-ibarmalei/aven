#pragma once


//#include <vector>
#include "textobject.h"
#include "enums/enummainmenuchoise.h"

class MainMenu
{
private:
    Init init;
    SimpleObject** mm_vector {nullptr};
    Plot*          startPoints {nullptr};
    int            mm_vectorLength {3};
    int menuChoise{ 0 };
    void  initStartPoints(const Texture* t);
    void initVector(const Texture* t);
public:
    explicit MainMenu(const Texture* t);
    void NextChoise();
    void PrevChoise();
    int GetChoise() const { return menuChoise; }
    bool Init_ok() const {return init.Init_ok();}
    ~MainMenu();
    SimpleObject* operator[](enumTextingOrder order);
};

