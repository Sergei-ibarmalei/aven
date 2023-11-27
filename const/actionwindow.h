#pragma once

#include "mainwindow.h"
#include "../types/rect.h"

constexpr int ACTIONWINDOW_SHIFT_X{ 10 };
constexpr int ACTIONWINDOW_SHIFT_Y{ 149 };

const Rect awindow 
{
    ACTIONWINDOW_SHIFT_X,
    ACTIONWINDOW_SHIFT_Y,
    MAINWINDOW_W - 2 * ACTIONWINDOW_SHIFT_X,
    MAINWINDOW_H - ACTIONWINDOW_SHIFT_X - ACTIONWINDOW_SHIFT_Y
};