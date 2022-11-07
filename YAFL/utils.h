#ifndef TESTS_UTILS_H
#define TESTS_UTILS_H

#include "fitsio.h"
#include <type_traits>
#include <cstdint>
#include <string>

namespace YAFL {
    enum DataType {
        t_string = TSTRING,
        t_logical = TLOGICAL,
        t_byte = TBYTE,
        t_short = TSHORT,
        t_ushort = TUSHORT,
        t_int = TINT,
        t_uint = TUINT,
        t_long = TLONG,
        t_longlong = TLONGLONG,
        t_ulong = TULONG,
        t_float = TFLOAT,
        t_double = TDOUBLE
    };

    enum HDUType {
        image = IMAGE_HDU,
        ascii_tbl = ASCII_TBL,
        binary_tbl = BINARY_TBL
    };

    enum ImageType {
        i_byte = BYTE_IMG,
        i_short = SHORT_IMG,
        i_long = LONG_IMG,
        i_longlong = LONGLONG_IMG,
        i_float = FLOAT_IMG,
        i_double = DOUBLE_IMG
    };

    template<typename T>
    constexpr int get_cfitsio_type() {
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
        } else if (std::is_same<T, long long>::value) {
            returned = TLONGLONG;
        } else if (std::is_same<T, u_long>::value) {
            returned = TULONG;
        } else if (std::is_same<T, float>::value) {
            returned = TFLOAT;
        } else if (std::is_same<T, double>::value) {
            returned = TDOUBLE;
        }
        return returned;
    }

    template<typename T>
    constexpr DataType get_datatype() {
        int type = get_cfitsio_type<T>();
        return (DataType)type;
    }
}

#endif //TESTS_UTILS_H
