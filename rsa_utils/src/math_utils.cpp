#include "math_utils.h"

namespace rsa_utils {

    /**
     * Find the greatest common divisor of a and b,
     * the highest value that a and b can both be divided by.
     * gcd
     */
    unsigned int euclidean_algorithm(unsigned int a, unsigned int b) {
        if (!b) return a;
        return euclidean_algorithm(b, a%b);
    }

    unsigned int lcm(unsigned int a, unsigned int b) {
        // avoid div 0
        if (!a && !b) return 0;
        return a*b / euclidean_algorithm(a,b);
    }

};