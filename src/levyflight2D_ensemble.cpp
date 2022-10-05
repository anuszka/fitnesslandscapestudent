#include "include/levyflight2D_ensemble.h"


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
        this->setInitialValues(this->X0);
        this->runSimulation();
        X_ens.push_back(this->X.back());
    }
    
}


void  LevyFlight2DEnsemble::printLastPoints(){
    this->printTimePos(X_ens);
}
