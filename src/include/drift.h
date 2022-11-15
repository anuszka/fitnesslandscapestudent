#include "timeposition.h"
#include "interpolation2d.h"

#ifndef DRIFT_H
#define DRIFT_H



double dVdx(double x);

position2D dVdx(position2D x);

position2D dVdx_test(position2D x);

position2D dVdx_test2(position2D x);

position2D dVdx_test3(position2D x);

double V_fitness_determ_test(position2D px);

position2D dVdx_fitness_determ_test(position2D px);

bool out_of_boundary_determ_test(position2D px,int file);

bool no_boundary_check(position2D px);

class intrpl
{
    public:
    intrpl(std::string potential_file_, std::string potential_file_second, int level);
    ~intrpl(){delete myinterp; delete griddata;}
    Interpolation2D *myinterp; // wskaznik do silnika liczacy interpolacje
    Interpolation2D *myinterp_second; // TN
    GridDataInterface *griddata;
    GridDataInterface *griddata_second; //TN
    double griddata_min_x;
    double griddata_min_y;
    double griddata_max_x;
    double griddata_max_y;
    double V(position2D px); 
    double V_second(position2D px);
    position2D dVdx(position2D px);
    position2D dVdx_second(position2D px);
    bool out_of_boundary_test(position2D px, int file);
    bool fitness_less_than_zero_test(position2D px, int file);
    GridDataInterface getGdi();
};


#endif