#include <gsl/gsl_math.h>
#include <gsl/gsl_sf_exp.h>
#include <string>
#include <iostream>
#include "include/drift.h"
#include "include/interpolation2d.h"
#include "include/griddatainterface.h"

double dVdx(double x)
{
    return (gsl_pow_3(x));
}

position2D dVdx(position2D px)
{
    position2D dvdx;
    dvdx.x = gsl_pow_3(px.x);
    dvdx.y = gsl_pow_3(px.y);
    return (dvdx);
}

position2D dVdx_test(position2D px)
{
    position2D dvdx;
    dvdx.x = 4. * gsl_pow_3(px.x + px.y);
    dvdx.y = 4 * (gsl_pow_3(px.x + px.y) + gsl_pow_3(px.y));
    return (dvdx);
}

position2D dVdx_test2(position2D px)
{
    position2D dvdx;
    // TODO: [LEV-51] gsl_sf_exp() returns underflow error. Diagnose with gsl_sf_exp_e()
    dvdx.x = (-0.5 + 5. * gsl_pow_4(px.x)) * exp(-gsl_pow_2(px.x) - gsl_pow_2(px.y)) - (2. * (1. - 0.5 * px.x + gsl_pow_5(px.x) + gsl_pow_3(px.y))) * px.x * exp(-gsl_pow_2(px.x) - gsl_pow_2(px.y));
    dvdx.y = 3. * gsl_pow_2(px.y) * exp(-gsl_pow_2(px.x) - gsl_pow_2(px.y)) - (2. * (1. - 0.5 * px.x + gsl_pow_5(px.x) + gsl_pow_3(px.y))) * px.y * exp(-gsl_pow_2(px.x) - gsl_pow_2(px.y));
    return (dvdx);
}

position2D dVdx_test3(position2D px)
{
    position2D dvdx;
    dvdx.x = (-0.5 + 5. * gsl_pow_4(px.x)) * exp(-gsl_pow_2(px.x) - gsl_pow_2(px.y)) - (2. * (1. - 0.5 * px.x + gsl_pow_5(px.x) + gsl_pow_3(px.y))) * px.x * exp(-gsl_pow_2(px.x) - gsl_pow_2(px.y)) + 0.1 * px.x;
    dvdx.y = 3. * gsl_pow_2(px.y) * exp(-gsl_pow_2(px.x) - gsl_pow_2(px.y)) - (2. * (1. - 0.5 * px.x + gsl_pow_5(px.x) + gsl_pow_3(px.y))) * px.y * exp(-gsl_pow_2(px.x) - gsl_pow_2(px.y)) + 0.1 * px.y;
    return (dvdx);
}

double V_fitness_determ_test(position2D px)
{
    return (.9 * px.x * px.y + 1863. / (1. + 1e-18 * gsl_pow_6(px.x) * gsl_pow_6(px.y)) - 2438.);
}

position2D dVdx_fitness_determ_test(position2D px)
{
    position2D dvdx;
    dvdx.x = 0.9 * px.y - 1.1178e-14 * gsl_pow_5(px.x) * gsl_pow_6(px.y) /
                              gsl_pow_2(1. + 1e-18 * gsl_pow_6(px.x) * gsl_pow_6(px.y));
    dvdx.y = 0.9 * px.x - 1.1178e-14 * gsl_pow_6(px.x) * gsl_pow_5(px.y) /
                              gsl_pow_2(1. + 1e-18 * gsl_pow_6(px.x) * gsl_pow_6(px.y));
    return (dvdx);
}

bool out_of_boundary_determ_test(position2D px)
{
    // Potential > 0. is equivalent to fitness < 0.
    return (px.x < 0. || px.y < 0. || V_fitness_determ_test(px) > 0.);
}

bool no_boundary_check(position2D px)
{
    return (true);
}

// TODO: [LEV-72] Define class for interpolation

intrpl::intrpl(std::string potential_file_)
{
    myinterp = new Interpolation2D;
    std::clog << "potential_file=" << potential_file_ << "\n";
    griddata = new GridDataInterface(potential_file_);
    myinterp->setData(*griddata);
    griddata_min_x = griddata->getXgrid().front();
    griddata_min_y = griddata->getYgrid().front();
    griddata_max_x = griddata->getXgrid().back();
    griddata_max_y = griddata->getYgrid().back();
}

double intrpl::V(position2D px)
{
    return (myinterp->getInterpolation(px.x, px.y));
}

position2D intrpl::dVdx(position2D px)
{
    position2D deriv;
    deriv.x = myinterp->getInterpolationDerivX(px.x, px.y);
    deriv.y = myinterp->getInterpolationDerivY(px.x, px.y);
    return (deriv);
}

bool intrpl::out_of_boundary_test(position2D px)
{
    // Returns true when some bounds are exceeded
    bool x_less_than_lower_bdr = (px.x < griddata_min_x);
    bool y_less_than_lower_bdr = (px.y < griddata_min_y);
    bool x_greater_than_upper_bdr = (px.x > griddata_max_x);
    bool y_greater_than_upper_bdr = (px.y > griddata_max_y);

    if (x_less_than_lower_bdr ||
        y_less_than_lower_bdr ||
        x_greater_than_upper_bdr ||
        y_greater_than_upper_bdr)
        return (true);
    else
        return (fitness_less_than_zero_test(px));
}

bool intrpl::fitness_less_than_zero_test(position2D px)
{
    // Potential > 0. is equivalent to fitness < 0.
    // Returns true (= out of bounds) when potential > 0., i.e., when fitness < 0.
    return (V(px) > 0.);
}
