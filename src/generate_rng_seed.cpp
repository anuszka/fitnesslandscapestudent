/*#include <sys/auxv.h>

// https://stackoverflow.com/questions/322938/recommended-way-to-initialize-srand
unsigned int setRngSeed(){
    unsigned int seed;
    seed = (unsigned int)getauxval(AT_RANDOM);
    return(seed);
}*/

#include <iostream>

unsigned int setRngSeed(){

    unsigned int seed;
    seed = static_cast<unsigned int>(time(nullptr));

    return (seed);

}
