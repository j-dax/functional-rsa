#include "math.hpp"

int euclidean_algorithm(int a, int b) {
    if (!b) return a;
    return euclidean_algorithm(b, a%b);
}