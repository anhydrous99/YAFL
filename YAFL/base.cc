#include "base.h"

#include <iostream>
#include <exception>

void YAFL::BaseFits::open(const std::string& path) {
    if (path.empty() && _path.empty())
        throw std::runtime_error("What file shall I open?");

    if (_path.empty())
        _path = path;
    
    int status = 0;
    fits_open_data(&_file_ptr, (char*)_path.c_str(), READONLY, &status);
    check_fits_status(status);
    _open = true;
}

void YAFL::BaseFits::close() {
    if (_open) {
        int status = 0;
        fits_close_file(_file_ptr, &status);
        if (status) {
            fits_report_error(stderr, status);
            throw;
        } else {
            _open = false;
        }
    }
}

void YAFL::BaseFits::check_fits_status(int status) {
    if (status) {
        fits_report_error(stderr, status);
        close();
        throw std::runtime_error("cfitsio error!");
    }
}

void YAFL::BaseFits::check_is_open() const {
    if (!_open)
        throw std::runtime_error("Can't use function without opening a fits file.");
}

YAFL::BaseFits::~BaseFits() {
    close();
}

int YAFL::BaseFits::n_keys() {
    int status = 0, nkeys;
    fits_get_hdrspace(_file_ptr, &nkeys, NULL, &status);
    return nkeys;
}

void YAFL::BaseFits::print_records() {
    check_is_open();
    
    int status = 0, nkeys;
    fits_get_hdrspace(_file_ptr, &nkeys, NULL, &status);

    char card[FLEN_CARD];
    for (int ii = 1; ii <= nkeys; ii++)  { 
        fits_read_record(_file_ptr, ii, card, &status); /* read keyword */
        std::cout << card << std::endl;
    }
}

YAFL::BaseFits::BaseFits(const std::string &path) {
    open(path);
}

int YAFL::BaseFits::num_hdus() {
    check_is_open();
    int num = 0, status = 0;
    fits_get_num_hdus(_file_ptr, &num, &status);
    check_fits_status(status);
    return num;
}

int YAFL::BaseFits::current_hdu() {
    check_is_open();
    int num = 0;
    fits_get_hdu_num(_file_ptr, &num);
    return num;
}

void YAFL::BaseFits::open_hdu(int n) {
    check_is_open();
    int status = 0;
    fits_movabs_hdu(_file_ptr, n, nullptr, &status);
    check_fits_status(status);
}

int YAFL::BaseFits::get_hdu_type() {
    check_is_open();
    int status = 0, hdutype = 0;
    fits_get_hdu_type(_file_ptr, &hdutype, &status);
    check_fits_status(status);
    return hdutype;
}

std::string YAFL::BaseFits::read_record(int keynum) {
    check_is_open();
    int status = 0;
    char card[FLEN_CARD];
    fits_read_record(_file_ptr, keynum, card, &status);
    check_fits_status(status);
    return {card};
}

std::string YAFL::BaseFits::read_card(const std::string &keyname) {
    check_is_open();
    int status = 0;
    char card[FLEN_CARD];
    fits_read_card(_file_ptr, (char*)keyname.c_str(), card, &status);
    check_fits_status(status);
    return {card};
}

template <>
std::tuple<std::string, std::string> YAFL::BaseFits::read_key(const std::string &keyname) {
    check_is_open();
    int type = get_fits_type<std::string>();
    int status = 0;
    char comment[FLEN_COMMENT];
    char output[FLEN_VALUE];
    fits_read_key(_file_ptr, type, (char*)keyname.c_str(), output, comment, &status);
    check_fits_status(status);
    return {std::string{output}, std::string{comment}};
}

std::string YAFL::BaseFits::read_key_comment(const std::string &keyname) {
    auto [_, comment] = read_key<std::string>(keyname);
    return comment;
}

std::string YAFL::BaseFits::read_key_unit(const std::string &keyname) {
    check_is_open();
    int status = 0;
    char unit[FLEN_COMMENT];
    fits_read_key_unit(_file_ptr, (char*)keyname.c_str(), unit, &status);
    check_fits_status(status);
    return {unit};
}

int YAFL::BaseFits::get_img_type() {
    check_is_open();
    int status = 0, type = 0;
    fits_get_img_type(_file_ptr, &type, &status);
    check_fits_status(status);
    return type;
}

int YAFL::BaseFits::get_img_dim() {
    check_is_open();
    int status = 0, naxis = 0;
    fits_get_img_dim(_file_ptr, &naxis, &status);
    check_fits_status(status);
    return naxis;
}

std::vector<long> YAFL::BaseFits::get_img_size() {
    int n_dims = get_img_dim();
    std::vector<long> sizes(n_dims, 0);
    int status = 0;
    fits_get_img_size(_file_ptr, n_dims, sizes.data(), &status);
    check_fits_status(status);
    return sizes;
}
