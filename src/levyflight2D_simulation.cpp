#include "include/exp_random.h"
#include "include/levyflight2D.h"
#include "include/timeposition.h"
#include <cmath>
#include <gsl/gsl_math.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>
#include <iostream>

timeposition2D LevyFlight2D::step(
    double delta_t,
    double prefactor,
    position2D gammadUdxXprev,
    timeposition2D X_prev,
    int file)
{

    timeposition2D X_new;
    X_new.t = X_prev.t + delta_t;
    // Boundary condition for fitness landscape
    // draw new position until within boundary
    do {
        X_new.pos.x = X_prev.pos.x - delta_t * gammadUdxXprev.x + prefactor * gsl_ran_levy(rng, D, alpha);
        X_new.pos.y = X_prev.pos.y - delta_t * gammadUdxXprev.y + prefactor * gsl_ran_levy(rng, D, alpha);
    } while (out_of_boundary(X_new.pos, file)); // TODO: [LEV-76] Chyba raczej while not out of boundary??

    // Boundary condition for fitness landscape
    // if x,y<0
    // if (X_new.pos.x < 0. || X_new.pos.y < 0.)
    // {
    //         X_new.pos.x = X_prev.pos.x;
    //         X_new.pos.y = X_prev.pos.y;
    // }
    return (X_new);
}

bool notZero(position2D X)
{
    return (!((X.x == 0.) || (X.y == 0.)));
}

double smallest_Dt_component(double eta, timeposition2D X_prev, position2D gammadUdxXprev)
{
    position2D Dt;
    double smallest_Dt_component;
    Dt.x = eta * X_prev.pos.x / gammadUdxXprev.x;
    Dt.y = eta * X_prev.pos.y / gammadUdxXprev.y;
    smallest_Dt_component = Dt.x < Dt.y ? Dt.x : Dt.y;
    return smallest_Dt_component;
}

void LevyFlight2D::runSimulation()
{

    std::map<double, int> timeRng = expRng(10, 30);
    std::map<double, int>::iterator itr = timeRng.begin();
    timeposition2D X_prev;
    timeposition2D X_new;
    double delta_t;
    double prefactor;
    double Dt;
    int file = 1;
    // static double tstart = 2;
    // static double tend = 2;
    position2D gammadUdxXprev;

    X_prev = X0;

    while (X_prev.t < T) {
        // TODO: [LEV-20] Value of dUdx(X_prev.x) must depend on X_prev.y. But not on dU/dy.
        // But then, Value of dUdy(X_prev.y) must depend on X_prev.x. But not on dU/dx.
        // TODO: [LEV-23] How to calculate Dt for 2D?
        // gammadUdxXprev = gamma * dUdx(X_prev.x);
        // std::cout<<X_prev.t<<"\n";
        // std::clog << "t=" << X_prev.t << " itr->first=" << itr->first << "\n";
        if (itr == timeRng.begin()) {
            gammadUdxXprev = gamma * dUdx(X_prev.pos);
        }
        if (X_prev.t > itr->first) {
            // std::clog << "t=" << X_prev.t << " itr->first=" << itr->first << "\n";
            // TODO: [LEV-81] Something is wrong with the value returned by itr->first
            /*
            t=151.099 itr->first=1.4822e-322
            t=151.199 itr->first=74.2312
            t=151.299 itr->first=1.4822e-322
            t=151.399 itr->first=74.2312
            t=151.499 itr->first=1.4822e-322
            t=151.599 itr->first=74.2312
            */
            itr++;

            if (file == 1) {
                gammadUdxXprev = gamma * dUdx_second(X_prev.pos);
                file = 2;
            } else {
                gammadUdxXprev = gamma * dUdx(X_prev.pos);
                file = 1;
            }

        } else {
            if (file == 1) {
                gammadUdxXprev = gamma * dUdx(X_prev.pos);
            } else {
                gammadUdxXprev = gamma * dUdx_second(X_prev.pos);
            }
        }

        if (notZero(gammadUdxXprev)) // denominator in eta * X_prev / gammadUdxXprev cannot be equal to 0
        {
            Dt = smallest_Dt_component(eta, X_prev, gammadUdxXprev);
            // TODO: [LEV-45] Check if dUdx() should be allowed to return negative values
            if ((dt < Dt) || (Dt < 0.)) { // Assuming that dt<Dt more often
                delta_t = dt;
                prefactor = pow_dt_1_alpha;
            } else {
                delta_t = Dt;
                if (delta_t < minDt) {
                    // std::clog << "Simulation stopped because delta_t < " << minDt << "\n\n";
                    // break;

                    // Warning! This is provisional! Simulation may diverge!
                    delta_t = minDt;
                }
                prefactor = pow(Dt, 1. / alpha);
            }
        } else {
            delta_t = dt;
            prefactor = pow_dt_1_alpha;
        }

        X_new = step(delta_t, prefactor, gammadUdxXprev, X_prev, file);
        setNewValues(X_new);

        if (gdi().isArea() && gdi().checkArea(X_new, Ntraj)) {
            break;
        }

        X_prev = X.back();
    }
}
