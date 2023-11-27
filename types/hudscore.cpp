#include "hudscore.h"


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


