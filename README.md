# Functional RSA

This project was started while learning about cmake, RSA, and functional programming. It is not meant to be used in a production setting. If you are looking for a secure cryptographic library in C, consider looking into [NaCl](https://nacl.cr.yp.to/index.html) or [OpenSSL](https://cmake.org/download/).

## Build

[CMake](https://cmake.org/download/) is used for building, testing and packaging. This project was built using MSVC 14.28.

```
cmake -B build -S . -Werror=deprecated
cmake --build build
```

## Testing

[GTest]() is used to test the code. Tests are found in the top level [*test*](master/test) folder with the *cc* extension. After building, the test executable is located in ./build/test/Debug 