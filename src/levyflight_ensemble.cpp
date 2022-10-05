#include "include/levyflight_ensemble.h"


void LevyFlightEnsemble::setNewValues(
        timeposition1D X_
        )
        {
        this->X.front() = this->X.back();
        this->X.back() = X_;
        }


void LevyFlightEnsemble::runMultipleSimulations(int N){
    for(int i=0; i<N; i++){
        this->X.clear();
        this->setInitialValues(this->X0);
        this->runSimulation();
        X_ens.push_back(this->X.back());
    }
    
}


void  LevyFlightEnsemble::printLastPoints(){
    this->printTimePos(X_ens);
}
