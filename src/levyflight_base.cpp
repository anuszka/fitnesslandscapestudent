#include <cstdio>
#include <gsl/gsl_math.h>
#include "include/levyflight_base.h"

LevyFlight_base::LevyFlight_base(){}


LevyFlight_base::~LevyFlight_base(){
        unsetRandomNumberGenerator();
}


void LevyFlight_base::setAlpha(double alpha_){alpha=alpha_;}


double LevyFlight_base::getAlpha(){return(alpha);}


void LevyFlight_base::setNoiseIntensity(double D_){D = D_;}


double LevyFlight_base::getNoiseIntensity(){return(D);}


void LevyFlight_base::setDriftIntensity(double gamma_){gamma = gamma_;}


double LevyFlight_base::getDriftIntensity(){return(gamma);}


void LevyFlight_base::setTimeStep(double dt_){dt=dt_;}

void LevyFlight_base::setMinimalTimeStep(double minDt_){minDt = minDt_;}


double LevyFlight_base::getTimeStep(){return(dt);}


void LevyFlight_base::setEndTime(double T_){T=T_;}


double LevyFlight_base::getEndTime(){return(T);}


void LevyFlight_base::setTpfsStart(double tstart){t_pfs_start=tstart;}

double LevyFlight_base::getTpfsStart(){return t_pfs_start;}


void LevyFlight_base::setTpfsEnd(double tend){t_pfs_end=tend;}

double LevyFlight_base::getTpfsEnd(){return t_pfs_end;}



void LevyFlight_base::setEta(double eta_){eta=eta_;}


double LevyFlight_base::getEta(){return(eta);}





void LevyFlight_base::printTraj(){}



void LevyFlight_base::setPrefactor()
{
        pow_dt_1_alpha = pow(dt, 1. / alpha);
}

void LevyFlight_base::runSimulation(){}
