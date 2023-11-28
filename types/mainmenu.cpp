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
