#include "include/timeposition.h"

position2D& position2D::operator=(const position2D &a)
    {
        x = a.x;
        y = a.y;
        return *this;
    }

position2D operator*(double n, position2D a)
    {
        position2D result;
        result.x = n*a.x;
        result.y = n*a.y;
        return result;
    }

position2D operator*(position2D a, double n)
    {
        position2D result;
        result.x = n*a.x;
        result.y = n*a.y;
        return result;
    }

timeposition2D& timeposition2D::operator=(const timeposition2D &a)
    {
        t = a.t;
        pos = a.pos;
        return *this;
    }