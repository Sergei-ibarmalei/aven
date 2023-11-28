#include "mainmenu.h"


MainMenu::MainMenu(const Texture* t)
{
    if (!t) { init.Negate(); return; }
    initStartPoints(t);
    initVector(t);
}

void MainMenu::initStartPoints(const Texture* t)
{
    const int step{(MAINWINDOW_H >> 2)};
    const int centerX{(MAINWINDOW_W >> 1) };
    startPoints = new Plot[3];

    for (auto i = static_cast<int>(enumTextingOrder::black_newgame);
        i < static_cast<int>(enumTextingOrder::red_newgame); i++)
    {
        startPoints[i].x = centerX - (t->operator[](i)->w >> 1);
        startPoints[i].y = ((i * step) + step) - (t->operator[](i)->h >> 1);
    }

}

void MainMenu::initVector(const Texture* t)
{

#define int_ static_cast<int>
    mm_vector = new SimpleObject * [int_(enumTextingOrder::all)];
    mm_vector[int_(enumTextingOrder::black_newgame)] = 
        new TextObject(t,startPoints[0], int_(enumTextingOrder::black_newgame));
    if (mm_vector[int_(enumTextingOrder::black_newgame)]->Init_ok() == false)
    {
        init.Negate(); return;
    }
    mm_vector[int_(enumTextingOrder::black_rules)] = 
        new TextObject(t,startPoints[1], int_(enumTextingOrder::black_rules));
    if (mm_vector[int_(enumTextingOrder::black_rules)]->Init_ok() == false)
    {
        init.Negate(); return;
    }
    mm_vector[int_(enumTextingOrder::black_exit)] = 
        new TextObject(t,startPoints[2], int_(enumTextingOrder::black_exit));
    if (mm_vector[int_(enumTextingOrder::black_exit)]->Init_ok() == false)
    {
        init.Negate(); return;
    }
    mm_vector[int_(enumTextingOrder::red_newgame)] = 
        new TextObject(t,startPoints[0], int_(enumTextingOrder::red_newgame));
    if (mm_vector[int_(enumTextingOrder::red_newgame)]->Init_ok() == false)
    {
        init.Negate(); return;
    }
    mm_vector[int_(enumTextingOrder::red_rules)] = 
        new TextObject(t, startPoints[1], int_(enumTextingOrder::red_rules));
    if (mm_vector[int_(enumTextingOrder::red_rules)]->Init_ok() == false)
    {
        init.Negate(); return;
    }
    mm_vector[int_(enumTextingOrder::red_exit)] = 
        new TextObject(t, startPoints[2], int_(enumTextingOrder::red_exit));     
    if (mm_vector[int_(enumTextingOrder::red_exit)]->Init_ok() == false)
    {
        init.Negate(); return;
    }

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
    delete[] startPoints;
    startPoints = nullptr;
    for (int i = 0; i < mm_vectorLength; ++i)
    {
        delete mm_vector[i];
        mm_vector[i] = nullptr;
    }
    delete[] mm_vector;
    mm_vector = nullptr;
}


SimpleObject* MainMenu::operator[](enumTextingOrder order)
{
    return mm_vector[static_cast<int>(order)];
}