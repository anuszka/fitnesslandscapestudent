#include "include/levyflight2D_ensemble.h"
#include <numeric>
#include <iostream>
#include <gsl/gsl_math.h>


void LevyFlight2DEnsemble::setNewValues(
        timeposition2D X_
        )
        {
        this->X.front() = this->X.back();
        this->X.back() = X_;
        }


void LevyFlight2DEnsemble::runMultipleSimulations(int N){
    for(int i=0; i<N; i++){
        this->X.clear();
        this->landscape_state.clear();
        this->setInitialValues(this->X0);
        this->setSwitchingTimes(mean_landscape_switching_times);
        this->runSimulation();
        X_ens.push_back(this->X.back());
    }
    
}


void  LevyFlight2DEnsemble::printLastPoints(){
    this->printTimePos(X_ens);
}

void LevyFlight2DEnsemble::averageTime(){
    if(X_ens.empty()){
        std::clog << "The Ensemble vector is empty\n";
    }else{
        double sum = 0;
        for(long long unsigned int i  = 0; i < X_ens.size(); i++){
            sum += X_ens[i].t;
        }
        
        avg = sum / X_ens.size();

        std::clog << "Average time of simulation: " << avg << "\n";

    }
}

void LevyFlight2DEnsemble::varianceTime(){

    if(X_ens.empty()){
        std::clog << "The Ensemble vector is empty\n";
    }else{
        double sum = 0;
        for(long long unsigned int i = 0; i < X_ens.size(); i++){

            sum += gsl_pow_2(X_ens[i].t - avg);
        }

        variance = sum / X_ens.size();

        std::clog << "Time simulation variance: " << variance << "\n";
    }
}