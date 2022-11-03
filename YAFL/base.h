#ifndef YAFL_WRAPPER_H
#define YAFL_WRAPPER_H

#include <fitsio.h>
#include <tuple>
#include <string>
#include <vector>

#include "utils.h"

namespace YAFL {
    class BaseFits {
        fitsfile* _file_ptr = nullptr;
        std::string _path;
        bool _open = false;

        void check_fits_status(int status);
        void check_is_open() const;
    public:
        void open(const std::string& path="");
        void close();

        BaseFits() = default;
        explicit BaseFits(const std::string& path);

        ~BaseFits();

        int n_keys();
        void print_records();
        int num_hdus();
        int current_hdu();
        void open_hdu(int n);
        int get_hdu_type();
        std::string read_record(int keynum);
        std::string read_card(const std::string& keyname);

        template <typename T> std::tuple<T, std::string> read_key(const std::string& keyname);
        template <typename T> T read_key_value(const std::string& keyname);
        std::string read_key_comment(const std::string& keyname);
        std::string read_key_unit(const std::string& keyname);
        int get_img_type();
        int get_img_dim();
        std::vector<long> get_img_size();
        long num_rows();
        int num_cols();
        int matching_col_num(const std::string& match, bool case_sensitive=false);
        std::string matching_col_name(const std::string& match, bool case_sensitive=false);
        std::vector<int> matching_col_nums(const std::string& match, bool case_sensitive=false);
        std::vector<std::string> matching_col_names(const std::string& match, bool case_sensitive=false);
    };
}

template <typename T>
std::tuple<T, std::string> YAFL::BaseFits::read_key(const std::string &keyname) {
    check_is_open();
    int type = get_fits_type<T>();
    int status = 0;
    char comment[FLEN_COMMENT];
    T ret;
    fits_read_key(_file_ptr, type, (char*)keyname.c_str(), &ret, comment, &status);
    check_fits_status(status);
    return {ret, std::string{comment}};
}

template <typename T>
T YAFL::BaseFits::read_key_value(const std::string &keyname) {
    auto [value, _] = read_key<T>(keyname);
    return value;
}

#endif // YAFL_WRAPPER_H