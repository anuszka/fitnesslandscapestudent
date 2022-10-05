#include "levyflight.h"

#ifndef LEVYFLIGHTENSEMBLE_H
#define LEVYFLIGHTENSEMBLE_H
class LevyFlightEnsemble : public LevyFlight{
    private: 
        std::vector<timeposition1D> X_ens; // Vector of final times and positions 
                                            // for an ensemble of trajectories, 
                                            // 1-D process 
        void setNewValues(
            timeposition1D X_
            ) override;
    public:
        void runMultipleSimulations(int N);
        void printLastPoints();
};

#endif