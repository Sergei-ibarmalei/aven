#pragma once

class ScoreBase
{
protected:
    int score{};
public:
    ScoreBase(const int objectScore): score(objectScore) {}
    int GetScore() const { return score; }
};

