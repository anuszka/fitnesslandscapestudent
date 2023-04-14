#include "include/exp_random.h"

std::map<double, int> expRng(double exp_dist_mean, int n)
{

    double const exp_dist_lambda = 1 / exp_dist_mean;

    std::random_device rd;
    std::exponential_distribution<> rng(exp_dist_lambda);
    std::mt19937 rnd_gen(rd());

    std::map<double, int> result_set;

    for (int i = 0; i < n; i++)
        ++result_set[(rng(rnd_gen) * 2)];

    return result_set;
}

