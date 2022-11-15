
#include <gsl/gsl_rng.h>

#ifndef LEVYFLIGHT_BASE_H
#define LEVYFLIGHT_BASE_H

class LevyFlight_base{
    private: 
        

    protected:
        gsl_rng* rng; // Random number generator
        const gsl_rng_type* rngType; // Random number generator type

        double alpha; // Levy parameter
        double D; // Noise intensity
        double gamma; // Drift intensity
        double dt; // Time step
        double minDt; // Minimal time step
        double T; // End time
        double eta; // Adaptive time step scaling factor
        double pow_dt_1_alpha; // Prefactor in Euler integration step
        int Ntraj;

        void setPrefactor();
        // TODO: [LEV-21] Make X a vector of 2D structures (double, double)
        // TODO: [LEV-22] Make X_curr, X_prev members. step() should use both of them

    public:
        LevyFlight_base(); // Constructor
        ~LevyFlight_base(); // Destructor
        
        void setAlpha(double alpha_);
        double getAlpha();
        void setNoiseIntensity(double D_);
        double getNoiseIntensity();
        void setDriftIntensity(double gamma_);
        double getDriftIntensity();
        
        void setTimeStep(double dt_);
        void setMinimalTimeStep(double minDt_);
        double getTimeStep();
        void setEndTime(double T_);
        double getEndTime();
        void setEta(double eta_);
        double getEta();
        void setRandomNumberGenerator(unsigned int seed);
        void unsetRandomNumberGenerator();
        virtual void runSimulation();
        virtual void printTraj();

    };


#endif