#include "rect.h"

std::ostream& operator<<(std::ostream& os, const Rect& r)
{
    os << "[x: " << r.x << ", y: " << r.y << ", w: " << r.w <<
        ", h: " << r.h << "]\n";
    return os;
}

