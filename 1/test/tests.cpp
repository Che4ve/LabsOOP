#include <gtest/gtest.h>
#include "../include/timecalc.h"

TEST(test_01, basic_test_get) {
    ASSERT_TRUE(convertTo24HourFormat(12, 22, "am") == "1222");
}

TEST(test_02, basic_test_get) {
    ASSERT_TRUE(convertTo24HourFormat(0, 30, "am") == "0030");
}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}