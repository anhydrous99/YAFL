#include "gtest/gtest.h"
#include "YAFL/base.h"
#include <iostream>

namespace {
    class TestBase : public testing::Test {
    protected:
        void SetUp() override {
            base_fits.open("tests/test-data/acisfJ0000082p135624_001N026_mrgsrc3.fits");
        }

        void TearDown() override {
            base_fits.close();
        }

        YAFL::BaseFits base_fits;
    };

    TEST_F(TestBase, TestPrintRecords) {
        testing::internal::CaptureStdout();
        base_fits.print_records();
        std::string output = testing::internal::GetCapturedStdout();
        std::string output_first = output.substr(0, output.find('\n'));
        std::string expected = "XTENSION= 'BINTABLE'           / binary table extension";
        EXPECT_EQ(expected, output_first);
    }

    TEST_F(TestBase, TestNumHDUS) {
        int num_hdus = base_fits.num_hdus();
        EXPECT_EQ(num_hdus, 7);
    }

    TEST_F(TestBase, TestCurrentHDU) {
        int current_hdu = base_fits.current_hdu();
        EXPECT_EQ(current_hdu, 2);
    }

    TEST_F(TestBase, TestHDUType) {
        int hdu_type = base_fits.get_hdu_type();
        EXPECT_EQ(hdu_type, BINARY_TBL);
    }

    TEST_F(TestBase, TestOpenHDU) {
        base_fits.open_hdu(3);
        EXPECT_EQ(base_fits.current_hdu(), 3);
    }

    TEST_F(TestBase, TestReadKeyRecord) {
        std::string record = base_fits.read_record(8);
        std::string expected{"TFIELDS =                   41 / number of fields in each row"};
        EXPECT_EQ(expected, record);
    }

    TEST_F(TestBase, TestReadKeyCard) {
        std::string card = base_fits.read_card("TFIELDS");
        std::string expected{"TFIELDS =                   41 / number of fields in each row"};
        EXPECT_EQ(expected, card);
    }

    TEST_F(TestBase, TestReadKeyUnit) {
        std::string unit = base_fits.read_key_unit("CONTENT");
        EXPECT_EQ(unit, ""); // This key has no unit
    }

    TEST_F(TestBase, TestReadKeyComment) {
        std::string comment = base_fits.read_key_comment("CONTENT");
        EXPECT_EQ(comment, "Level3 file mrgsrc3 file");
    }

    TEST_F(TestBase, TestReadKeyStringValue) {
        auto value = base_fits.read_key_value<std::string>("CONTENT");
        EXPECT_EQ(value, "mrgsrc");
    }

    TEST_F(TestBase, TestReadKeyIntValue) {
        int value = base_fits.read_key_value<int>("TFIELDS");
        EXPECT_EQ(value, 41);
    }

    TEST_F(TestBase, TestReadKey) {
        auto [value, comment] = base_fits.read_key<std::string>("CONTENT");
        EXPECT_EQ(value, "mrgsrc");
        EXPECT_EQ(comment, "Level3 file mrgsrc3 file");
    }
}