#include "googletest/googletest/include/gtest/gtest.h"

TEST(ConstructorTests, TestArgs) {

    EXPECT_EQ(3, 3);
}
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}