#include "print.h"

template<typename T>
void output_container(std::ostream& os, std::vector<T> container) {
    std::cout << "[ ";
    std::copy(container.begin(),container.end(),std::ostream_iterator<T>(os, ", "));
    std::cout << " ]" << std::endl;
}