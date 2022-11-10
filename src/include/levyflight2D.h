#include <vector>
#include "timeposition.h"
#include "levyflight_base.h"
#include "drift.h"

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
        position2D (*func_second)(position2D), // TN
        bool (*func_bdr)(position2D,int),
        double dt,
        double minDt,
        double eta,
        double T,
        double t_pfs_start,
        double t_pfs_end,
        timeposition2D X0,
        unsigned int seed,
        GridDataInterface (*func_gdi)() = NULL
        );

    void runSimulation() override;
    void printTraj() override;
};

#endif