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

double LevyFlight2D::getMean_landscape_switching_times()
{
    return (mean_landscape_switching_times);
}

void LevyFlight2D::setInitialValues(timeposition2D X0_)
{
    X0 = X0_;
    X.push_back(X0);
}

void LevyFlight2D::setSwitchingTimes(double mean)
{
    double number, cumul = 0.;
    // Remove all elements from the queue
    while(! switching_times.empty())
        switching_times.pop();
    while (cumul < T) {
        number = gsl_ran_exponential(rng, mean);
        switching_times.push(cumul + number);
        cumul += number;
    }
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
    mean_landscape_switching_times = 10;
    setSwitchingTimes(mean_landscape_switching_times);
}

void LevyFlight2D::printTimePos(std::vector<timeposition2D> timepos)
{
    for (
        auto X_ = timepos.begin();
        X_ != timepos.end();
        X_++)
        printf("%f,%f,%f\n", (*X_).t, (*X_).pos.x, (*X_).pos.y);
}

void LevyFlight2D::printTimePosLandscape(std::vector<timeposition2D> timepos, std::vector<timeposition1D> landscape_st)
{
    auto L_ = landscape_st.begin();

    for (
        auto X_ = timepos.begin();
        X_ != timepos.end();
        X_++, L_++)
        printf("%f,%f,%f,%f,%f\n", (*X_).t, (*X_).pos.x, (*X_).pos.y, (*L_).t, (*L_).x);
}

void LevyFlight2D::printTraj()
{
    printTimePosLandscape(X, landscape_state);
}

void LevyFlight2D::setNewValues(
    timeposition2D X_)
{
    X.push_back(X_);
}

void LevyFlight2D::setNewValues(
    timeposition1D X_)
{
    landscape_state.push_back(X_);
}