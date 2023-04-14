#include "include/levyflight2D.h"
#include <cstdio>
#include <gsl/gsl_math.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>
#include <iostream>

LevyFlight2D::LevyFlight2D() { }

LevyFlight2D::~LevyFlight2D()
{
}

void LevyFlight2D::setInitialValues(timeposition2D X0_)
{
    X0 = X0_;
    X.push_back(X0);
}

void LevyFlight2D::setSwitchingTimes(double mean, int n)
{
    double number, cumul = 0.;
    std::clog << "----------------\nExp rng test\n";
    std::clog << "cumul,number\n";
    for (int i = 0; i < n; ++i) {
        number = gsl_ran_exponential(rng, mean);
        std::clog << cumul << "," << number << "\n";
        switching_times.push(cumul + number);
        cumul += number;
    }
    std::clog << "\n---------------------\n";
}

double LevyFlight2D::getInitialTime() { return (X0.t); }

double LevyFlight2D::getInitialPositionX() { return (X0.pos.x); }
double LevyFlight2D::getInitialPositionY() { return (X0.pos.y); }

void LevyFlight2D::setParams(
    double alpha,
    double D,
    double gamma,
    double (*func_U)(position2D),
    position2D (*func)(position2D),
    position2D (*func_second)(position2D),
    bool (*func_bdr)(position2D, int),
    double dt,
    double minDt,
    double eta,
    double T,
    timeposition2D X0,
    unsigned int seed,
    GridDataInterface (*func_gdi)(),
    int nt)
{
    setAlpha(alpha);
    setNoiseIntensity(D);
    setDriftIntensity(gamma);
    U = func_U;
    dUdx = func;
    dUdx_second = func_second;
    out_of_boundary = func_bdr;
    setTimeStep(dt);
    setMinimalTimeStep(minDt);
    setEta(eta);
    setPrefactor();
    setEndTime(T);
    setInitialValues(X0);
    setRandomNumberGenerator(seed);
    gdi = func_gdi;
    Ntraj = nt;
    N_landscape_switching_times = 5;
    mean_landscape_switching_times = 10;
    setSwitchingTimes(mean_landscape_switching_times, N_landscape_switching_times);
}

void LevyFlight2D::printTimePos(std::vector<timeposition2D> timepos)
{
    for (
        auto X_ = timepos.begin();
        X_ != timepos.end();
        X_++)
        printf("%f,%f,%f\n", (*X_).t, (*X_).pos.x, (*X_).pos.y);
}

void LevyFlight2D::printTraj()
{
    printTimePos(X);
}

void LevyFlight2D::setNewValues(
    timeposition2D X_)
{
    X.push_back(X_);
}
