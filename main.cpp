#include "types/core/game.h"


int main(int argc, char* argv[])
{
    Game game;
    if (game.Init_ok() == false) return 1;
    return 0;
}