#include "base.h"

#include <iostream>

void YAFL::BaseFits::open(const std::string path="") {
    if (path.empty() && _path.empty())
        throw "What file shall I open?";

    if (_path.empty())
        _path = path;
    
    int status;
    fits_open_file(&_file_ptr, (char*)_path.c_str(), READONLY, &status);
    check_fits_status(status);
    _open = true;
}

void YAFL::BaseFits::close() {
    if (_open) {
        int status;
        fits_close_file(_file_ptr, &status);
        check_fits_status(status);
    }
}

void YAFL::BaseFits::check_fits_status(int status) {
    if (status)
        fits_report_error(stderr, status);
        close();
        throw;
}

YAFL::BaseFits::~BaseFits() {
    close();
}

int YAFL::BaseFits::n_keys() {
    int status, nkeys;
    fits_get_hdrspace(_file_ptr, &nkeys, NULL, &status);
    return nkeys;
}

void YAFL::BaseFits::print_records() {
    if (!open)
        throw "File must be open";
    
    int status, nkeys;
    fits_get_hdrspace(_file_ptr, &nkeys, NULL, &status);

    char card[FLEN_CARD];
    for (int ii = 1; ii <= nkeys; ii++)  { 
        fits_read_record(_file_ptr, ii, card, &status); /* read keyword */
        std::cout << card;
    }
}

YAFL::BaseFits::BaseFits(const std::string &path) {
    open(path);
}
