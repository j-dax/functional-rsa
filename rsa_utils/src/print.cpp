#include "print.h"

template<typename T>
void print_iterator(std::list<T> it) {
    std::cout << "[ ";
    std::copy(it.begin(),it.end(),std::ostream_iterator<T>(std::cout, ", "));
    std::cout << " ]" << std::endl;
}