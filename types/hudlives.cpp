#include "hudlives.h"


HUD_lives::HUD_lives(const Texture* t)
{
#define int_ static_cast<int>
    if (!t)
    {
        init.Negate(); return;
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
#define int_ static_cast<int>
    const int stepx{ 187 };
    const int y{ 61 };


    centers[int_(enumHudLivesPosition::left)].x = stepx;
    centers[int_(enumHudLivesPosition::left)].y = y;
    centers[int_(enumHudLivesPosition::center)].x = 2 * stepx;
    centers[int_(enumHudLivesPosition::center)].y = y;
    centers[int_(enumHudLivesPosition::right)].x = 3 * stepx;
    centers[int_(enumHudLivesPosition::right)].y = y;
#undef int_
}
