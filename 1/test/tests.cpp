#include <gtest/gtest.h>
#include "../include/timecalc.h"

TEST(BASIC, test_01) {
    ASSERT_TRUE(convertTo24HourFormat(0, 0, "am") == "0000");
}

TEST(BASIC, test_02) {
    ASSERT_TRUE(convertTo24HourFormat(0, 0, "pm") == "1200");
}

TEST(BASIC, test_03) {
    ASSERT_TRUE(convertTo24HourFormat(0, 3, "am") == "0003");
}

TEST(BASIC, test_04) {
    ASSERT_TRUE(convertTo24HourFormat(4, 30, "am") == "0430");
}

TEST(BASIC, test_05) {
    ASSERT_TRUE(convertTo24HourFormat(0, 30, "pm") == "1230");
}

TEST(BASIC, test_06) {
       ASSERT_TRUE(convertTo24HourFormat(11, 30, "pm") == "2330");
}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}