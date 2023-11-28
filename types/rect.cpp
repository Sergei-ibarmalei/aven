#include "rect.h"

std::ostream& operator<<(std::ostream& os, const Rect& r)
{
    os << "[x: " << r.x << ", y: " << r.y << ", w: " << r.w <<
        ", h: " << r.h << "]\n";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Plot& p)
{
    os << "[x: " << p.x << ", y: " << p.y << "]\n";
    return os;
}

