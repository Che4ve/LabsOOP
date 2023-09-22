#include <gtest/gtest.h>
#include "../include/timecalc.h"

TEST(test_01, basic_test_get) {
    ASSERT_TRUE(convertTo24HourFormat(0, 0, "am") == "0000");
}

TEST(test_02, basic_test_get) {
    ASSERT_TRUE(convertTo24HourFormat(0, 0, "pm") == "1200");
}

TEST(test_03, basic_test_get) {
    ASSERT_TRUE(convertTo24HourFormat(0, 3, "am") == "0003");
}

TEST(test_04, basic_test_get) {
    ASSERT_TRUE(convertTo24HourFormat(4, 30, "am") == "0430");
}

TEST(test_05, basic_test_get) {
    ASSERT_TRUE(convertTo24HourFormat(0, 30, "pm") == "1230");
}

TEST(test_06, basic_test_get) {
       ASSERT_TRUE(convertTo24HourFormat(11, 30, "pm") == "2330");
}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}