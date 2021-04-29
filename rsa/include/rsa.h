#include "common.h"
#include "math_utils.h"

namespace rsa {

    void generate_key();
    
    void encrypt_message();
    void add_padding_();

    void decrypt_message();
    void remove_padding_();
    // void distribute_key(target);
    void sign_message();
    
    // void serialize(std::string path, keys k);

    void save_key(std::string path);
    void load_key(std::string path);

    struct RSAPrivate {
        unsigned int p;
        unsigned int q;
    };

    struct RSAPublic {
        unsigned int n;
        unsigned int e;
    };

};