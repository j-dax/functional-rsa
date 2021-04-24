#pragma once

#include "common.h"
#include <list>

unsigned int euclidean_algorithm(unsigned int a, unsigned int b);
unsigned int lcm(unsigned int a, unsigned int b);
std::list<unsigned int> find_coprimes(unsigned int n);
unsigned int euler_totient(unsigned int prime);
unsigned int carmichael_totient(unsigned int n);