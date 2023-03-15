#include "googletest/googletest/include/gtest/gtest.h"
#include "../CheckersEngine/Src/GameLogic/Checker.cpp"
#include "../CheckersEngine/Src/GameLogic/Board.cpp"
//#include "../CheckersEngine/Src/main.cpp"
#include "../CheckersEngine/Src/GameLogic/Player.cpp"
#include "../CheckersEngine/Src/GameLogic/GameLogic.cpp"
#include "../CheckersEngine/Src/Vector2D.cpp"
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
TEST(CheckerTests, TestChangeColor) {


    Checker* checker = new Checker(0, 0, 'B');
    checker->change('R');
    ASSERT_EQ(checker->getColor(), 'R');

}
TEST(PlayerTests, TestConstructor) {
    Player* player = new Player('R');
    player->setColor('B');
    ASSERT_EQ(player->getColor(), 'B');
}
TEST(PlayerTests, TestChangeColor) {
    Player* player = new Player();
    player->setColor('B');
    ASSERT_EQ(player->getColor(), 'B');
}
TEST(GameLogicTests, TestConstructorTurns) {
    GameLogic* logic = new GameLogic();
    ASSERT_EQ(logic->getCurrPlayer(), 'R');
}
TEST(GameLogicTests, TestConstructorPlayer) {
    GameLogic* logic = new GameLogic();
    ASSERT_EQ(logic->getPlayer().getColor(), 'R');
}
TEST(GameLogicTests, TestChangeTurns) {
    GameLogic* logic = new GameLogic();
    EXPECT_EQ(logic->getCurrPlayer(), 'R');
    logic->changeTurns();
    ASSERT_EQ(logic->getCurrPlayer(), 'B');
}
TEST(VectorTests, TestConstructor1) {
    Vector2D* vector = new Vector2D();
    EXPECT_EQ(vector->x, 0);
    ASSERT_EQ(vector->y, 0);
}
TEST(VectorTests, TestConstructor2) {
    Vector2D* vector = new Vector2D(0.5f,0.5f);
    EXPECT_FLOAT_EQ(vector->x, 0.5f);
    ASSERT_FLOAT_EQ(vector->y, 0.5f);
}
TEST(VectorTests, TestAdd) {
    Vector2D* vector1 = new Vector2D();
    Vector2D* vector2 = new Vector2D(0.5f,0.5f);
    vector1->Add(*vector2);
    EXPECT_FLOAT_EQ(vector1->x, 0.5f);
    ASSERT_FLOAT_EQ(vector1->y, 0.5f);
}
TEST(VectorTests, TestSubtract) {
    Vector2D* vector1 = new Vector2D(1.0f, 1.0f);
    Vector2D* vector2 = new Vector2D(0.5f, 0.5f);
    vector1->Subtract(*vector2);
    EXPECT_FLOAT_EQ(vector1->x, 0.5f);
    ASSERT_FLOAT_EQ(vector1->y, 0.5f);
}
TEST(VectorTests, TestMultiply) {
    Vector2D* vector1 = new Vector2D();
    Vector2D* vector2 = new Vector2D(0.5f, 0.5f);
    vector1->Multiply(*vector2);
    EXPECT_FLOAT_EQ(vector1->x, 0.0f);
    ASSERT_FLOAT_EQ(vector1->y, 0.0f);
}
TEST(VectorTests, TestDivide) {
    Vector2D* vector1 = new Vector2D();
    Vector2D* vector2 = new Vector2D(0.5f, 0.5f);
    vector1->Divide(*vector2);
    EXPECT_FLOAT_EQ(vector1->x, 0.0f);
    ASSERT_FLOAT_EQ(vector1->y, 0.0f);

}
TEST(VectorTests, TestOperatorAdd) {
    Vector2D vector1(0.5f,0.5f);
    Vector2D vector2(0.5f, 0.5f);
    Vector2D vector3 = vector1 + vector2;
    EXPECT_FLOAT_EQ(vector3.x, 1.0f);
    ASSERT_FLOAT_EQ(vector3.y, 1.0f);

}
TEST(VectorTests, TestOperatorSubtract) {
    Vector2D vector1(0.5f, 0.5f);
    Vector2D vector2(0.5f, 0.5f);
    Vector2D vector3 = vector1 - vector2;
    EXPECT_FLOAT_EQ(vector3.x, 0.0f);
    ASSERT_FLOAT_EQ(vector3.y, 0.0f);

}
TEST(VectorTests, TestOperatorMultiply) {
    Vector2D vector1(0.5f, 0.5f);
    Vector2D vector2(0.5f, 0.5f);
    Vector2D vector3 = vector1 * vector2;
    EXPECT_FLOAT_EQ(vector3.x, 0.25f);
    ASSERT_FLOAT_EQ(vector3.y, 0.25);

}
TEST(VectorTests, TestOperatorDivide) {
    Vector2D vector1(0.5f, 0.5f);
    Vector2D vector2(0.5f, 0.5f);
    Vector2D vector3 = vector1 / vector2;
    EXPECT_FLOAT_EQ(vector3.x, 1.0f);
    ASSERT_FLOAT_EQ(vector3.y, 1.0);

}
TEST(BoardTests, TestConstructor) {

}
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}