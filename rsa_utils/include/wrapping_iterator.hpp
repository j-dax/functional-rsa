#pragma once

#include <iterator>

namespace rsa {

    template <typename T>
    class WrappingIterator : std::forward_iterator<T> {
        private:
        T *begin_it, *end_it;
        size_t index;

        public:
        // WrappingIterator(); // don't allow default
        WrappingIterator(T container) {
            begin_it = std::begin(container);
            end_it = std::end(container);
            index = 0;
        }
        WrappingIterator(T container, size_t start_index) {
            begin_it = std::begin(container);
            end_it = std::end(container);
            index = start_index;
        }
        ~WrappingIterator() {
            delete begin_it;
            delete end_it;
        }
        
        T* begin() {
            return begin_it;
        }
        T* end() {
            return end_it;
        }

        T* operator++() {
            index++;
            index %= (end_it - begin_it);
            return (begin_it + index);
        }
    };

};