#include "base.h"

#include <iostream>
#include <exception>

void YAFL::BaseFits::open(const std::string& path) {
    if (path.empty() && _path.empty())
        throw std::runtime_error("What file shall I open?");

    if (_path.empty())
        _path = path;
    
    int status = 0;
    fits_open_file(&_file_ptr, (char*)_path.c_str(), READONLY, &status);
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

YAFL::BaseFits::~BaseFits() {
    close();
}

int YAFL::BaseFits::n_keys() {
    int status = 0, nkeys;
    fits_get_hdrspace(_file_ptr, &nkeys, NULL, &status);
    return nkeys;
}

void YAFL::BaseFits::print_records() {
    if (!_open)
        throw std::runtime_error("File must be open");
    
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
