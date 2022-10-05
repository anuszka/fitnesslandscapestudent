#ifndef TIMEPOSITION_H
#define TIMEPOSITION_H

struct timeposition1D{ // Position coordinates, 1-D process + time
    double t;
    double x;
    timeposition1D& operator=(const timeposition1D& a)
    {
        t=a.t;
        x=a.x;
        return *this;
    }
};

struct position2D
{
    double x;
    double y; 
    position2D(){};
    position2D(double x_, double y_) : x(x_), y(y_){}
    position2D &operator=(const position2D &a);
};



struct timeposition2D
{ // Position coordinates, 2-D process + time
    double t;
    position2D pos;

    timeposition2D &operator=(const timeposition2D &a);
};


position2D operator*(double n, position2D a);
position2D operator*(position2D a, double n);

#endif