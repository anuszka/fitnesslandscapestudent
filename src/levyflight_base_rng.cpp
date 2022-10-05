#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include "include/levyflight_base.h"

void LevyFlight_base::setRandomNumberGenerator(unsigned int seed){
    /* create a generator chosen by the environment variable GSL_RNG_TYPE */
    gsl_rng_env_setup();

    rngType = gsl_rng_default;
    rng = gsl_rng_alloc(rngType);

    gsl_rng_set(rng, seed);
}

void LevyFlight_base::unsetRandomNumberGenerator(){
    gsl_rng_free (rng);
}
