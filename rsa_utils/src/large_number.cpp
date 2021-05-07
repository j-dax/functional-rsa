#include "large_number.h"

namespace rsa {

    LargeNumber::LargeNumber() : little_endian({0}) {}
    LargeNumber::LargeNumber(uint8_t i) : little_endian({i}) {}
    LargeNumber::LargeNumber(const std::vector<uint8_t> v) : little_endian(v) {}
    LargeNumber::LargeNumber(const LargeNumber& n) {
        // TEST: verify these are different structures after copy constructed
        little_endian = std::vector<uint8_t>(n.little_endian);
    }

    std::vector<uint8_t> LargeNumber::vector() const { return little_endian; }
    void LargeNumber::trim_() {
        while(little_endian.size() > 0 && little_endian.back() == 0)
            little_endian.pop_back();
    } // helper function, drop trailing 0s
    LargeNumber LargeNumber::reverse_() const {
        std::vector<uint8_t> big_endian_number;
        std::copy_backward(little_endian.begin(), little_endian.end(), big_endian_number.begin());
        return big_endian_number;
    }
    size_t LargeNumber::places_() const {
        return little_endian.size();
    }

    uint8_t& LargeNumber::operator[](size_t i) {
        size_t size = little_endian.size();
        while (i >= size++)
            little_endian.push_back(0);
        return little_endian.at(i);
    }
    uint8_t LargeNumber::operator[](size_t i) const {
        if (i >= little_endian.size()) return 0;
        return little_endian.at(i);
    }

    // bitwise operations
    LargeNumber LargeNumber::not() const {
        LargeNumber output = LargeNumber();
        output[places_()] = 0;

        std::transform(little_endian.begin(), little_endian.end(),
            output.little_endian.begin(), [](uint8_t i) {
                return UINT8_MAX ^ i;
        });

        output.trim_();
        return output;
    }
    LargeNumber LargeNumber::operator!() const {
        return this->not();
    }
    LargeNumber LargeNumber::or(const LargeNumber& that) const {
        LargeNumber output = LargeNumber();
        auto places = std::max(places_(), that.places_());
        output[places - 1] = 0;

        std::copy(little_endian.begin(), little_endian.end(), output.little_endian.begin());

        std::transform(that.little_endian.begin(), that.little_endian.end(),
            output.little_endian.begin(), output.little_endian.begin(),
            [](uint8_t lhs, uint8_t rhs) {
                return lhs | rhs;
            });

        output.trim_();
        return output;
    }
    LargeNumber LargeNumber::operator|(const LargeNumber& that) const {
        return this->or(that);
    }
    LargeNumber LargeNumber::and(const LargeNumber& that) const {
        LargeNumber output = LargeNumber();
        output[places_()] = 0;

        std::transform(little_endian.begin(), little_endian.end(),
            that.little_endian.begin(), output.little_endian.begin(),
            [](uint8_t lhs, uint8_t rhs) {
                return lhs & rhs;
            });

        return output;
    }
    LargeNumber LargeNumber::operator&(const LargeNumber& that) const {
        return this->and(that);
    }

    bool LargeNumber::operator>(const LargeNumber& that) const {
        size_t max_index = std::max(this->places_(), that.places_());
        for (size_t i = max_index; i > 0; i--) {
            if ((*this)[i-1] != that[i-1]) return (*this)[i-1] > that[i-1];
        }
        return false;
    }
    bool LargeNumber::operator>=(const LargeNumber& that) const {
        size_t max_index = std::max(this->places_(), that.places_());
        for (size_t i = max_index; i > 0; i--) {
            if ((*this)[i-1] != that[i-1]) return (*this)[i-1] > that[i-1];
        }
        return true; // survived loop, all must be eq
    }
    bool LargeNumber::operator<(const LargeNumber& that) const {
        size_t max_index = std::max(this->places_(), that.places_());
        for (size_t i = max_index; i > 0; i--) {
            if ((*this)[i-1] != that[i-1]) return (*this)[i-1] < that[i-1];
        }
        return false;
    }
    bool LargeNumber::operator<=(const LargeNumber& that) const {
        size_t max_index = std::max(this->places_(), that.places_());
        for (size_t i = max_index; i > 0; i--) {
            if ((*this)[i-1] != that[i-1]) return (*this)[i-1] < that[i-1];
        }
        return true;
    }
    // size mismatch is valid. equal if leading zeros
    bool LargeNumber::operator==(const LargeNumber& that) const {
        size_t max_index = std::max(this->places_(), that.places_());
        for (size_t i = max_index; i > 0; i--) {
            if ((*this)[i-1] != that[i-1]) return false;
        }
        return true;
    }
    bool LargeNumber::operator!=(const LargeNumber& that) const {
        return !(*this == that);
    }

    // wrap around is monitored through the carry reference
    uint8_t plus_(uint8_t a, uint8_t b, bool& carry) {
        uint8_t value = a+b + (uint8_t)(carry?1:0);
        carry = (UINT8_MAX - a < b + (uint8_t)(carry?1:0));
        return value;
    }

    // simple arithmetic, flavor
    LargeNumber LargeNumber::plus_helper_(const LargeNumber& that, bool& carry) const {
#define DEBUG_LARGE_PLUS 0
        size_t max_places = std::max(this->places_(), that.places_()) + 1;
        LargeNumber output = LargeNumber();
        for (auto i = 0; i < max_places; i++) {

#if DEBUG_LARGE_PLUS
            std::cout   << "\t" << (unsigned int)(*this)[i] << " " << (unsigned int)that[i]
                        << (carry?" TRUE":" FALSE") << " => ";
#endif // DEBUG

            output[i] = plus_((*this)[i], that[i], carry);

#if DEBUG_LARGE_PLUS
            std::cout   << (int)output[i] << (carry?" TRUE":" FALSE") << "\n\t\t" << output << std::endl;
#endif // DEBUG
        }
        // add the carry to the last used position
        if (carry) output[max_places-1]++;
        // the last position is always not necessary, pop if 0
        output.trim_();
        return output;
    }
    LargeNumber LargeNumber::plus(const LargeNumber& that) const { // this + that
        bool _ = false;
        return plus_helper_(that, _);
    }
    LargeNumber LargeNumber::operator+(const LargeNumber& that) const { // this + that
        return plus(that);
    }
    LargeNumber LargeNumber::minus(const LargeNumber& that) const {
        // short circuit if lhs < rhs
        if ((*this) < that) return {0};
        // make sure output has same # of places as that
        bool carry = false;
        LargeNumber output = LargeNumber(that);
        output[std::max(output.places_(), this->places_())-1] += 0;
        // before output.not is called.
        output = plus_helper_(output.not()+LargeNumber({1}), carry);
        // 0x0 - 0x0 -> 0x0 + 0xFF + 0x1 -> 0x100 - 0x100 = 0x0
        // drop the final place by one so the value matches the result
        output[output.places_()-1]-=1;
        output.trim_();
        return output;
    }
    LargeNumber LargeNumber::operator-(const LargeNumber& that) const { // this - that
        return minus(that);
    }

};