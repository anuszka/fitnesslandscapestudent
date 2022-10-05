#include <vector>
#include "levyflight_base.h"
#include "timeposition.h"

#ifndef LEVYFLIGHT_H
#define LEVYFLIGHT_H



class LevyFlight : public LevyFlight_base{
    private: 
        

    protected:
    
        timeposition1D X0; // Initial coordinates: time + position
        
        std::vector<timeposition1D> X;// Time + position vector, 1-D process
        double (*dUdx)(double); // dU/dx drift 1D
        
        timeposition1D step( 
            double delta_t, 
            double prefactor, 
            double gammadUdxXprev, 
            timeposition1D X_prev
            );


        void printTimePos(std::vector<timeposition1D> timepos);
        
        virtual void setNewValues(timeposition1D X_); 


    public:
        LevyFlight(); // Constructor
        ~LevyFlight(); // Destructor
        
        void setInitialValues(timeposition1D X0);
        double getInitialTime();
        double getInitialPosition();
        
        //TODO: [LEV-46] Should first call parent's setParams to set parent's member variables.
        void setParams(
            double alpha,
            double D,
            double gamma,
            double (*func)(double),
            double dt,
            double minDt,
            double eta,
            double T,
            timeposition1D X0,
            unsigned int seed
            );
        
        void runSimulation() override;
        void printTraj() override;
    };

#endif