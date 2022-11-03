//
// Created by Armando Herrera on 11/2/22.
//

#ifndef TESTS_UTILS_H
#define TESTS_UTILS_H

#include "fitsio.h"
#include <type_traits>
#include <cstdint>
#include <string>

template<typename T>
constexpr int get_fits_type() {
    int returned = -1;
    if (std::is_same<T, std::string>::value) {
        returned = TSTRING;
    } else if (std::is_same<T, bool>::value) {
        returned = TLOGICAL;
    } else if (std::is_same<T, uint8_t>::value) {
        returned = TBYTE;
    } else if (std::is_same<T, short>::value) {
        returned = TSHORT;
    } else if (std::is_same<T, ushort>::value) {
        returned = TUSHORT;
    } else if (std::is_same<T, int>::value) {
        returned = TINT;
    } else if (std::is_same<T, uint>::value) {
        returned = TUINT;
    } else if (std::is_same<T, long>::value) {
        returned = TLONG;
    } else if (std::is_same<T, u_long>::value) {
        returned = TULONG;
    } else if (std::is_same<T, float>::value) {
        returned = TFLOAT;
    } else if (std::is_same<T, double>::value) {
        returned = TDOUBLE;
    }
    return returned;
}

#endif //TESTS_UTILS_H
