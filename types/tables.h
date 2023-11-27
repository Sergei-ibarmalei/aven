#pragma once

#include <math.h>

//Класс для хранения таблиц Брадиса по синусу
class TableSin
{
private:
    const int tableLength = 180;
    double* vsin = nullptr;
public:
    TableSin();
    ~TableSin();
    double operator[](const int index);
};

//Класс для хранения таблицы по косинусу
class TableCos
{
    private:
    const int tableLength = 180;
    double* vcos = nullptr;

    public:
    TableCos();
    ~TableCos();
    double operator[](const int index);
};
