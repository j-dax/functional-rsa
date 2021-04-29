#include "common.h"

namespace rsa_utils {
    
    std::list<unsigned int> find_coprimes(unsigned int n);
    unsigned int euler_totient(unsigned int prime);
    unsigned int carmichael_totient(unsigned int n);
    bool is_prime(unsigned int n);

}