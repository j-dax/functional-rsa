#include "math.hpp"
#include <vector>
#include <algorithm>

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
    return abs(a*b) / euclidean_algorithm(a,b);
}

/**
 * Numbers are coprime if they share no common factors,
 * in other words, their gcd is 1.
 */
bool coprime(unsigned int a, unsigned int b) {
    return euclidean_algorithm(a,b) == 1;
}

/**
 * The magnitude of coprimes is at most n - 1. By definition, coprimes of
 * a prime number are all positive numbers less than it.
 */
std::vector<unsigned int> find_coprimes(unsigned int n) {
    // std::vector<unsigned int> v();
    // for (auto i = 0; i < n; i++) {
    //     coprime(i,n) && v.push_back(i);
    // }
    // return v;
    // functional attempt 1:
    if (n <= 2) return {1};
    
    std::vector<unsigned int> coprimes = {1};
    auto _ = std::copy_if(2, n, std::back_inserter(coprimes), coprime);
    return coprimes;
}

// auto aboveEighty = [](Student student) { return student.score() > 80; };
//  vector<Student> topStudents = {};
//  auto it = std::copy_if(students.begin(), students.end(), back_inserter(topStudents), aboveEighty);
//  std::for_each(topStudents.begin(), topStudents.end(), printStudentDetails);

unsigned int euler_totient(unsigned int n) {
    return find_coprimes(n).size();
}

unsigned int carmichael_totient(unsigned int n) {
    unsigned int min = n; // not valid, should be overwritten by std::min
    std::vector<unsigned int> original = find_coprimes(n), power;
    std::copy(original, power); // 1
    std::for_each(start, end, [](int a){

    })    
}

int * arr() {
    return {1,2,3,4,5,6,7,8,9,10};
}