#include <cstdio>
#include <gsl/gsl_math.h>
#include "include/levyflight.h"

LevyFlight::LevyFlight(){}


LevyFlight::~LevyFlight(){
}



void LevyFlight::setInitialValues(timeposition1D X0_)
        {
        X0= X0_;
        X.push_back(X0);
        }


double LevyFlight::getInitialTime(){return(X0.t);}


double LevyFlight::getInitialPosition(){return(X0.x);}


void LevyFlight::setParams(
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
        )
        {
        setAlpha(alpha);
        setNoiseIntensity(D);
        setDriftIntensity(gamma);
        dUdx=func;
        setTimeStep(dt);
        setMinimalTimeStep(minDt);
        setEta(eta);
        setPrefactor();
        setEndTime(T);
        setInitialValues(X0);
        setRandomNumberGenerator(seed);
        }



void LevyFlight::printTimePos(std::vector<timeposition1D> timepos){
        for(
                auto X_ = timepos.begin(); 
                X_!=timepos.end(); 
                X_++
        ) 
        printf("%f,%f\n", (*X_).t, (*X_).x);
}



void LevyFlight::printTraj(){
        printTimePos(X);
}


void LevyFlight::setNewValues(
        timeposition1D X_
        )
        {
        X.push_back(X_);
        }



