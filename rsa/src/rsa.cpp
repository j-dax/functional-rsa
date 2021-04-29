#include "rsa.h"

namespace rsa {

    /**
     * Choose two distinct p and q. They must be prime
     * compute p*q, this is shared.
     * compute carmichael(n) or lcm(p-1,q-1)
     * Choose an integer, e, such that 3 < e < carmichael(n) && gcd(e, carmichael(n)) == 1
     * Calculate d from d===e^-1 % carmichael(n)
     */
    void generate_key() {

    }

    // void serialize(std::string path, keys k) {}

    void save_key(std::string path) {}
    void load_key(std::string path) {}
        
    void encrypt_message() {}
    void add_padding_() {}

    void decrypt_message() {}
    void remove_padding_() {}
    // void distribute_key(target) {}?
    void sign_message() {}

}