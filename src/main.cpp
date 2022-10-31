#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "include/levyflight_launch.h"

int main(int argc, char **argv)
{
    LevyFlightLaunch lfl(argc, argv);
    if (argc < 10 || argc > 17) // TN 14 -> 15  15 -> 17
        lfl.printUsage();

    else
    {
        lfl.parseArgs();
        lfl.logParsed();

        if (lfl.dimensions == 1)
            if (lfl.Ntraj == 1)
                lfl.launch_1D_1traj();
            else
                lfl.launch_1D_ensemble();
        else if (lfl.dimensions == 2)
        {
            if (lfl.Ntraj == 1 && lfl.potentialFileIsEmpty())
                lfl.launch_2D_1traj();
            else if (lfl.Ntraj == 1 && !lfl.potentialFileIsEmpty())
                lfl.launch_2D_1traj_potential_file();
            else if (lfl.Ntraj > 1 && lfl.potentialFileIsEmpty())
                lfl.launch_2D_ensemble(); 
            else if (lfl.Ntraj > 1 && !lfl.potentialFileIsEmpty())
                lfl.launch_2D_ensemble_potential_file(); // TODO: [LEV-79] Ensemble with potential file
        }

        std::clog << "Output written to STDOUT.\n";
        std::clog << "Done.\n\n";
    }

    return EXIT_SUCCESS;
}