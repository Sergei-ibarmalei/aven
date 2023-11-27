#pragma once
#include "rect.h"

constexpr int HUD_SCORE_LENGTH{ 5 };

class HUD_score
{
private:
    int gameScore{};
    const Plot HUD_SCORE_CENTER{ 1685, 61 };
    const int delimeter[HUD_SCORE_LENGTH]{ 10'000, 1000, 100, 10, 1 };
    Rect  hudScoreMainRects[HUD_SCORE_LENGTH];
    int   hudScore[HUD_SCORE_LENGTH]{};


    void initHudScoreMainRects();

public:
    HUD_score();
    HUD_score(const HUD_score&) = delete;
    HUD_score& operator=(const HUD_score&) = delete;
    void SetScore(int score);
    const Rect* HudScoreMainRects()    const { return hudScoreMainRects; }
    const int* HudScore() const { return hudScore; }
    void ResetGameScore();

};

