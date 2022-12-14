#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "YAFL/base.h"
#include <iostream>

namespace {
    class TestBaseTable : public testing::Test {
    protected:
        void SetUp() override {
            base_fits.open("tests/test-data/acisfJ0000082p135624_001N026_mrgsrc3.fits");
        }

        void TearDown() override {
            base_fits.close();
        }

        YAFL::BaseFits base_fits;
    };

    class TestBaseImage : public testing::Test {
    protected:
        void SetUp() override {
            base_fits.open("tests/test-data/acisfJ0013281p405149_001N021_b_img3.fits");
        }

        void TearDown() override {
            base_fits.close();
        }

        YAFL::BaseFits base_fits;
    };

    TEST_F(TestBaseTable, TestPrintRecords) {
        testing::internal::CaptureStdout();
        base_fits.print_records();
        std::string output = testing::internal::GetCapturedStdout();
        std::string output_first = output.substr(0, output.find('\n'));
        std::string expected = "XTENSION= 'BINTABLE'           / binary table extension";
        EXPECT_EQ(expected, output_first);
    }

    TEST_F(TestBaseTable, TestNumHDUS) {
        int num_hdus = base_fits.num_hdus();
        EXPECT_EQ(num_hdus, 7);
    }

    TEST_F(TestBaseTable, TestCurrentHDU) {
        int current_hdu = base_fits.current_hdu();
        EXPECT_EQ(current_hdu, 2);
    }

    TEST_F(TestBaseTable, TestHDUType) {
        auto hdu_type = base_fits.get_hdu_type();
        EXPECT_EQ(hdu_type, YAFL::HDUType::binary_tbl);
    }

    TEST_F(TestBaseTable, TestOpenHDU) {
        base_fits.open_hdu(3);
        EXPECT_EQ(base_fits.current_hdu(), 3);
    }

    TEST_F(TestBaseTable, TestOpenHDUName) {
        base_fits.open_hdu("WAVSRC", YAFL::HDUType::binary_tbl);
        EXPECT_EQ(base_fits.current_hdu(), 4);
    }

    TEST_F(TestBaseTable, TestReadKeyRecord) {
        std::string record = base_fits.read_record(8);
        std::string expected{"TFIELDS =                   41 / number of fields in each row"};
        EXPECT_EQ(expected, record);
    }

    TEST_F(TestBaseTable, TestReadKeyCard) {
        std::string card = base_fits.read_card("TFIELDS");
        std::string expected{"TFIELDS =                   41 / number of fields in each row"};
        EXPECT_EQ(expected, card);
    }

    TEST_F(TestBaseTable, TestReadKeyUnit) {
        std::string unit = base_fits.read_key_unit("CONTENT");
        EXPECT_EQ(unit, ""); // This key has no unit
    }

    TEST_F(TestBaseTable, TestReadKeyComment) {
        std::string comment = base_fits.read_key_comment("CONTENT");
        EXPECT_EQ(comment, "Level3 file mrgsrc3 file");
    }

    TEST_F(TestBaseTable, TestReadKeyStringValue) {
        auto value = base_fits.read_key_value<std::string>("CONTENT");
        EXPECT_EQ(value, "mrgsrc");
    }

    TEST_F(TestBaseTable, TestReadKeyIntValue) {
        int value = base_fits.read_key_value<int>("TFIELDS");
        EXPECT_EQ(value, 41);
    }

    TEST_F(TestBaseTable, TestReadKey) {
        auto [value, comment] = base_fits.read_key<std::string>("CONTENT");
        EXPECT_EQ(value, "mrgsrc");
        EXPECT_EQ(comment, "Level3 file mrgsrc3 file");
    }

    TEST_F(TestBaseImage, TestGetImgType) {
        auto type = base_fits.get_img_type();
        EXPECT_EQ(type, YAFL::ImageType::i_double);
    }

    TEST_F(TestBaseImage, TestGetImgDim) {
        int dim = base_fits.get_img_dim();
        EXPECT_EQ(dim, 2);
    }

    TEST_F(TestBaseImage, TestGetImgSize) {
        auto shape = base_fits.get_img_size();
        ASSERT_THAT(shape, testing::ElementsAre(1074, 329));
    }

    TEST_F(TestBaseTable, TestNRows) {
        long n_rows = base_fits.num_rows();
        EXPECT_EQ(n_rows, 34);
    }

    TEST_F(TestBaseTable, TestNCols) {
        int n_cols = base_fits.num_cols();
        EXPECT_EQ(n_cols, 41);
    }

    TEST_F(TestBaseTable, TestMatchColNum) {
        int col_num = base_fits.matching_col_num("component");
        EXPECT_EQ(col_num, 1);
    }

    TEST_F(TestBaseTable, TestMatchColName) {
        std::string col_name = base_fits.matching_col_name("comp*");
        EXPECT_EQ(col_name, "component");
    }

    TEST_F(TestBaseTable, TestMatchColNums) {
        auto col_nums = base_fits.matching_col_nums("man_*_flag");
        ASSERT_THAT(col_nums, testing::ElementsAre(8, 9, 10, 11));
    }

    TEST_F(TestBaseTable, TestMatchColNames) {
        auto col_names = base_fits.matching_col_names("man_*_flag");
        ASSERT_THAT(col_names, testing::ElementsAre("man_add_flag", "man_inc_flag", "man_reg_flag", "man_pos_flag"));
    }

    TEST_F(TestBaseTable, TestGetColType) {
        auto type1 = base_fits.get_column_type(1);
        auto type2 = base_fits.get_eqcolumn_type(1);

        EXPECT_EQ(TLONG, type1.typecode);
        EXPECT_EQ(1, type1.repeat);
        EXPECT_EQ(4, type1.width);
        EXPECT_EQ(TLONG, type2.typecode);
        EXPECT_EQ(1, type2.repeat);
        EXPECT_EQ(4, type2.width);
    }
}