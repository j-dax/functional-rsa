#pragma once

#include "common.h"

namespace rsa {

    template <typename T>
    std::ostream& output_container(std::ostream& os, const std::vector<T>& container) {
        os << "[";
        std::copy(container.begin(), container.end(), std::ostream_iterator<int>(os, " "));
        os << "]";
        return os;
    }

    uint8_t plus_(uint8_t, uint8_t, bool&);

    // treat the base as 2^8, or 1 byte length
    class LargeNumber {
    private:
        std::vector<uint8_t> little_endian;
    public:
        LargeNumber();
        LargeNumber::LargeNumber(uint8_t);
        LargeNumber(const std::vector<uint8_t>);
        LargeNumber(const LargeNumber&);

        // helper functions
        std::vector<uint8_t> LargeNumber::vector() const;
        void trim_(); // drop trailing 0s
        LargeNumber reverse_() const; // reverse
        size_t places_() const;

        uint8_t& operator[](size_t); // index assignment
        uint8_t operator[](size_t) const; // index
        
        // bitwise operations
        LargeNumber not() const;
        LargeNumber operator!() const;
        LargeNumber or(const LargeNumber&) const;
        LargeNumber operator|(const LargeNumber&) const;
        LargeNumber and(const LargeNumber&) const;
        LargeNumber operator&(const LargeNumber&) const;

        // comparison
        bool operator>(const LargeNumber&) const;
        bool operator>=(const LargeNumber&) const;
        bool operator<(const LargeNumber&) const;
        bool operator<=(const LargeNumber&) const;
        bool operator==(const LargeNumber&) const;
        bool operator!=(const LargeNumber&) const;

        // simple arithmetic, flavor
        LargeNumber plus_helper_(const LargeNumber&, bool&) const;
        LargeNumber plus(const LargeNumber&) const;
        LargeNumber operator+(const LargeNumber&) const; // this + that
        LargeNumber minus(const LargeNumber&) const;
        LargeNumber operator-(const LargeNumber&) const; // this - that
        // LargeNumber operator%(const LargeNumber) const; // this % that

        friend std::ostream& operator<<(std::ostream& os, LargeNumber n) {
            output_container(os, n.little_endian);
            return os;
        }

    };

};