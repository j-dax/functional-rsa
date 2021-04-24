#include "math_utils.h"

#define DEBUG 1

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

/**
 * The magnitude of coprimes is at most n - 1. By definition, coprimes of
 * a prime number are all positive numbers less than it.
 */
std::list<unsigned int> find_coprimes(unsigned int n) {
    if (n <= 2) return {1};

    auto not_coprime = std::bind([](unsigned int a, unsigned int b)
        { return euclidean_algorithm(a,b) != 1; },
        n,
        std::placeholders::_1
    );
    std::list<unsigned int> coprimes(n);
    std::iota(coprimes.begin(), coprimes.end(), 1);
    
    coprimes.erase(
        std::remove_if(coprimes.begin(), coprimes.end(), not_coprime),
        coprimes.end());

    return coprimes;
}

template<typename T>
void print_iterator(std::list<T> it) {
    std::cout << "[ ";
    std::copy(it.begin(),it.end(),std::ostream_iterator<T>(std::cout, ", "));
    std::cout << " ]" << std::endl;
}

unsigned int euler_totient(unsigned int n) {
    return find_coprimes(n).size();
}

/** carmichael totient is a lower bound of the euler totient
 * the solution is the smallest such m where all values satisfy base[i]**m == 1modn
 * modulo arithmetic helps here, (ab) % n === ((a%n)(b%n))%n
 */
unsigned int carmichael_totient(unsigned int n) {
    if (n <= 2) return 1;

    std::list<unsigned int> base = find_coprimes(n);
    // number is prime, primes are n-1
    if (base.size() == n - 1) return n-1;

    std::list<unsigned int> power_list(base.size());
    std::copy(base.begin(), base.end(), power_list.begin());
    // 
    auto mod_n_is_one = std::bind([&](unsigned int a, unsigned int bind_n) {
        return a % bind_n == 1;
    }, std::placeholders::_1, n);
    auto modulo_multiplies = std::bind([&](unsigned int a, unsigned int b, unsigned int c){
        return (a % c * b % c) % c;
    }, std::placeholders::_1, std::placeholders::_2, n);

    unsigned int power = 2;
    for (power; power < base.size(); power++) {
        std::transform(base.begin(), base.end(), power_list.begin(),
            power_list.begin(), modulo_multiplies);
        if (std::all_of(power_list.begin(), power_list.end(), mod_n_is_one))
            break;
    }

    return power;
}
