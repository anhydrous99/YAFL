#ifndef YAFL_WRAPPER_H
#define YAFL_WRAPPER_H

#include <fitsio.h>
#include <string>

namespace YAFL {
    class BaseFits {
        fitsfile* _file_ptr;
        std::string _path;
        bool _open = false;

        void check_fits_status(int status);
    public:
        void open(const std::string path="");
        void close();

        BaseFits() = default;
        explicit BaseFits(const std::string& path);

        ~BaseFits();

        int n_keys();
        void print_records();
    };
}

#endif // YAFL_WRAPPER_H