#include<iostream>
#include<random>
#include<iomanip>
#include<map>
#include<stack>
#include<iterator>


#ifndef EXP_RANDOM_H
#define EXP_RANDOM_H

std::map<double, int> expRng(double exp_dist_mean, int n );
std::stack<double> exp_random_numbers(double exp_dist_mean, int n );

#endif