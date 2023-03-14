#include "googletest/googletest/include/gtest/gtest.h"
#include "../CheckersEngine/Src/GameLogic/Checker.cpp"
TEST(CheckerTests, TestIsKingedBlack) {
    coord c;
    c.x = 7;//Kinging criteria for black piece
    c.y = 0;
    Checker* checker = new Checker(0, 0, 'B');
    EXPECT_EQ(checker->getisKinged(), false);
    checker->changePosition(c);
    ASSERT_EQ(checker->getisKinged(), true);
}
TEST(CheckerTests, TestIsKingedRed) {
    coord c;
    c.x = 0;//Kinging criteria for red piece
    c.y = 0;
    Checker* checker = new Checker(1, 0, 'R');
    EXPECT_EQ(checker->getisKinged(), false);
    checker->changePosition(c);
    ASSERT_EQ(checker->getisKinged(), true);
}
TEST(CheckerTests, TestConstructor) {

    
    Checker* checker = new Checker(0, 0, 'B');
    EXPECT_EQ(checker->getPosition().x, 0);
    
}
TEST(CheckerTests, TestChangePosition) {

    coord c;
    c.x = 0;
    c.y = 0;
    Checker* checker = new Checker(2, 5, 'B');
    checker->changePosition(c);
    EXPECT_EQ(checker->getPosition().x, 0);

}
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}