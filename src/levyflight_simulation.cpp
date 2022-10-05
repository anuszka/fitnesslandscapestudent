#include <cmath>
#include <iostream>
#include <gsl/gsl_math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include "include/levyflight.h"

timeposition1D LevyFlight::step(
    double delta_t,
    double prefactor,
    double gammadUdxXprev,
    timeposition1D X_prev)
{

        timeposition1D X_new;
        X_new.t = X_prev.t + delta_t;
        X_new.x = X_prev.x - delta_t * gammadUdxXprev + prefactor * gsl_ran_levy(rng, D, alpha);

        return (X_new);
}

void LevyFlight::runSimulation()
{

        timeposition1D X_prev;
        timeposition1D X_new;
        double delta_t;
        double prefactor;
        double Dt;
        double gammadUdxXprev;

        X_prev = X0;

        while (X_prev.t < T)
        {
                // TODO: [LEV-20] Value of dUdx(X_prev.x) must depend on X_prev.y. But not on dU/dy.
                // But then, Value of dUdy(X_prev.y) must depend on X_prev.x. But not on dU/dx.
                // TODO: [LEV-23] How to calculate Dt for 2D?
                gammadUdxXprev = gamma * dUdx(X_prev.x);

                if (gammadUdxXprev != 0.) // denominator in eta * X_prev / gammadUdxXprev cannot be equal to 0
                {
                        Dt = eta * X_prev.x / gammadUdxXprev;
                        if ((dt < Dt) || (Dt < 0.))
                        { // Assuming that dt<Dt more often
                                delta_t = dt;
                                prefactor = pow_dt_1_alpha;
                        }
                        else
                        {
                                delta_t = Dt;
                                if (delta_t < minDt)
                                {
                                        std::clog << "Simulation stopped because delta_t < " << minDt << "\n\n";
                                        break;
                                }
                                prefactor = pow(Dt, 1. / alpha);
                        }
                }
                else
                {
                        delta_t = dt;
                        prefactor = pow_dt_1_alpha;
                }

                X_new = step(delta_t, prefactor, gammadUdxXprev, X_prev);
                setNewValues(X_new);
                X_prev = X.back();
        }
}
