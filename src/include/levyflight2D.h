#include <vector>
#include "timeposition.h"
#include "levyflight_base.h"

#ifndef LEVYFLIGHT2D_H
#define LEVYFLIGHT2D_H

class LevyFlight2D : public LevyFlight_base
{
private:
protected:
    timeposition2D X0; // Initial coordinates: time + position

    std::vector<timeposition2D> X; // Time + position vector, 1-D process
    double (*U)(position2D); // 2D potential
    position2D (*dUdx)(position2D); // 2D drift: Gradient of the potential
    bool (*out_of_boundary)(position2D X); // Check boundary

    timeposition2D step(
        double delta_t,
        double prefactor,
        position2D gammadUdxXprev,
        timeposition2D X_prev);

    void printTimePos(std::vector<timeposition2D> timepos);

    virtual void setNewValues(timeposition2D X_);

public:
    LevyFlight2D();  // Constructor
    ~LevyFlight2D(); // Destructor

    void setInitialValues(timeposition2D X0);
    double getInitialTime();
    double getInitialPositionX();
    double getInitialPositionY();

    void setParams(
        double alpha,
        double D,
        double gamma,
        double (*func_U)(position2D),
        position2D (*func)(position2D),
        bool (*func_bdr)(position2D),
        double dt,
        double minDt,
        double eta,
        double T,
        timeposition2D X0,
        unsigned int seed);

    void runSimulation() override;
    void printTraj() override;
};

#endif