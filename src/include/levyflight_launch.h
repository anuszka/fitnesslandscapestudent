#ifndef LEVYFLIGHTLAUNCH_H
#define LEVYFLIGHTLAUNCH_H

#include "drift.h"
class LevyFlightLaunch
{
private:
    int argc;
    char **argv;
    double alpha;               // Levy parameter
    double D;                   // Noise intensity
    double gamma;               // Drift intensity
    double dt;                  // Time step
    double minDt;               // Minimal adaptive time step
    double eta;                 // Adaptive time step scaling factor
    double T;                   // End time
    double t0;                  // Initial time
    double x0;                  // Initial position x
    double y0;                  // Initial position y
    double kmr1;                // Lower limit of kmr
    double kmr2;                // Upper limit of kmr
    double kr1;                 // Lower limit of kr
    double kr2;                 // Upper limit of kr
    int lvl;                    // Potential level
    unsigned int seed;          // Random number generator seed
    // char *potentialfile;       // Potential grid file
    std::string potential_file; // Potential grid file
    std::string potential_file_second;// TN // second Potential grif file
public:
    unsigned int Ntraj; // Number of trajectories
    int dimensions;     // Number of dimensions

    LevyFlightLaunch(int argc_, char **argv_) : argc(argc_), argv(argv_) {}
    ~LevyFlightLaunch(){};
    void printUsage();
    bool potentialFileIsEmpty() { return (potential_file.empty()); }
    // void setPotentialFile(char *potentialfile);
    void parseArgs();
    void logParsed();
    void launch_1D_1traj();
    void launch_2D_1traj();
    void launch_1D_ensemble();
    void launch_2D_ensemble();
    void launch_2D_1traj_potential_file();
    void launch_2D_ensemble_potential_file();
};

#endif