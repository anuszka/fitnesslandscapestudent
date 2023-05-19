#include "drift.h"
#include "levyflight_base.h"
#include "timeposition.h"
#include <queue>
#include <vector>

#ifndef LEVYFLIGHT2D_H
#define LEVYFLIGHT2D_H

class LevyFlight2D : public LevyFlight_base {
private:
protected:
    double mean_landscape_switching_times;

    std::queue<double> switching_times; // Times when the fitness landscape switches

    timeposition2D X0; // Initial coordinates: time + position

    std::vector<timeposition2D> X; // Time + position vector, 2-D process
    std::vector<timeposition1D> landscape_state; // Time + landscape state vector, 1-D process

    double (*U)(position2D); // 2D potential
    position2D (*dUdx)(position2D); // 2D drift: Gradient of the potential
    bool (*out_of_boundary)(position2D X, int); // Check boundary
    GridDataInterface (*gdi)();

    position2D (*dUdx_second)(position2D);

    timeposition2D step(
        double delta_t,
        double prefactor,
        position2D gammadUdxXprev,
        timeposition2D X_prev,
        int file);

    void printTimePos(std::vector<timeposition2D> timepos);
    void printTimePosLandscape(std::vector<timeposition2D> timepos, std::vector<timeposition1D> landscape_st);


    virtual void setNewValues(timeposition2D X_);
    virtual void setNewValues(timeposition1D X_);

    public:
        LevyFlight2D(); // Constructor
        ~LevyFlight2D(); // Destructor

        void setInitialValues(timeposition2D X0);

        void setSwitchingTimes(double mean);

        double getInitialTime();
        double getInitialPositionX();
        double getInitialPositionY();
        double getMean_landscape_switching_times();

        void setParams(
            double alpha,
            double D,
            double gamma,
            double (*func_U)(position2D),
            position2D (*func)(position2D),
            position2D (*func_second)(position2D), // TN
            bool (*func_bdr)(position2D, int),
            double dt,
            double minDt,
            double eta,
            double T,
            timeposition2D X0,
            double mean_landscape_switching_times,
            unsigned int seed,
            GridDataInterface (*func_gdi)() = NULL,
            int nt = 1
            );

        void runSimulation() override;
        void printTraj() override;
    };

#endif