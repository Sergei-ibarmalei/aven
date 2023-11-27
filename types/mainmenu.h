#pragma once


#include <vector>
#include "textobject.h"
#include "enums/enummainmenuchoise.h"

class MainMenu : public Init
{
private:
    std::vector<SimpleObject*> mm_vector;
    std::vector<Plot> startPoints;
    int menuChoise{ 0 };
    void  initStartPoints(const Texture* t);
    void initVector(const Texture* t);
public:
    explicit MainMenu(const Texture* t);
    void NextChoise();
    void PrevChoise();
    const std::vector<SimpleObject*>& GetMainMenu() const { return mm_vector; }
    int GetChoise() const { return menuChoise; }
    ~MainMenu();
};

