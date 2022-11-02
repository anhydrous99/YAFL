#include "gtest/gtest.h"
#include "YAFL/base.h"
#include <iostream>

namespace {
    TEST(TestBase, TestPrintRecords) {
        auto base_fits = YAFL::BaseFits("tests/test-data/acisfJ0000082p135624_001N026_mrgsrc3.fits");

        testing::internal::CaptureStdout();
        base_fits.print_records();
        std::string output = testing::internal::GetCapturedStdout();
        std::string output_first = output.substr(0, output.find('\n'));
        std::string expected = "SIMPLE  =                    T / file does conform to FITS standard";
        EXPECT_EQ(expected, output_first);
    }
}