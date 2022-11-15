#include "levyflight2D.h"

#ifndef LEVYFLIGHT2DENSEMBLE_H
#define LEVYFLIGHT2DENSEMBLE_H

class LevyFlight2DEnsemble : public LevyFlight2D{
    private: 
        std::vector<timeposition2D> X_ens; // Vector of final times and positions 
                                            // for an ensemble of trajectories, 
                                            // 1-D process 
        void setNewValues(
            timeposition2D X_
            ) override;

        double avg;
        double variance;
        
    public:
        void runMultipleSimulations(int N);
        void printLastPoints();
        void averageTime();
        void varianceTime();
};



#endif