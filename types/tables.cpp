#include "tables.h"

TableCos::TableCos()
{
    const double rad = 3.14159265/180.0;
    vcos = new double[tableLength];
    for (int i = 0; i < tableLength; i++)
    {
        vcos[i] = cos(static_cast<double>(i) * rad);
    }
}

double TableCos::operator[](const int index)
{
    if (index < 0) return vcos[0];
    if (index > tableLength) return vcos[tableLength];
    return vcos[index];
}

TableCos::~TableCos()
{
    delete[] vcos;
    vcos = nullptr;
}

TableSin::TableSin()
{
    const double rad = 3.14159265/180.0;
    vsin = new double[tableLength];
    for (int i = 0; i < tableLength; i++)
    {
        vsin[i] = sin(static_cast<double>(i) * rad);
    }
}

double TableSin::operator[](const int index)
{
    if (index < 0) return vsin[0];
    if (index > tableLength) return vsin[tableLength];
    return vsin[index];
}

TableSin::~TableSin()
{
    delete[] vsin;
    vsin = nullptr;
}
