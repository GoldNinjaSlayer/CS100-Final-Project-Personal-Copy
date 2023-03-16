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
    EXPECT_FLOAT_EQ(vector->x, 0);
    ASSERT_FLOAT_EQ(vector->y, 0);
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
TEST(VectorTests, TestOperatorPlusEqual) {
    Vector2D vector1(0.5f, 0.5f);
    Vector2D vector2(0.5f, 0.5f);
    vector1 += vector2;
    EXPECT_FLOAT_EQ(vector1.x, 1.0f);
    ASSERT_FLOAT_EQ(vector1.y, 1.0);

}
TEST(VectorTests, TestOperatorMinusEqual) {
    Vector2D vector1(0.5f, 0.5f);
    Vector2D vector2(0.5f, 0.5f);
    vector1 -= vector2;
    EXPECT_FLOAT_EQ(vector1.x, 0.0f);
    ASSERT_FLOAT_EQ(vector1.y, 0.0f);

}
TEST(VectorTests, TestOperatorTimesEqual) {
    Vector2D vector1(0.5f, 0.5f);
    Vector2D vector2(0.5f, 0.5f);
    vector1 *= vector2;
    EXPECT_FLOAT_EQ(vector1.x, 0.25f);
    ASSERT_FLOAT_EQ(vector1.y, 0.25);

}
TEST(VectorTests, TestOperatorDivEqual) {
    Vector2D vector1(0.5f, 0.5f);
    Vector2D vector2(0.5f, 0.5f);
    vector1 /= vector2;
    EXPECT_FLOAT_EQ(vector1.x, 1.0f);
    ASSERT_FLOAT_EQ(vector1.y, 1.0);

}
TEST(VectorTests, TestZeroFunction) {
    Vector2D* vector = new Vector2D(1.0f,1.0f);
    vector->Zero();
    EXPECT_FLOAT_EQ(vector->x, 0.0);
    ASSERT_FLOAT_EQ(vector->y, 0.0);
}
TEST(BoardTests, TestConstructor) {
    Board* board = new Board(8);
    EXPECT_EQ(board->getchecker(0, 2)->getColor(), 'B');
    EXPECT_EQ(board->getchecker(0, 5)->getColor(), '0');
    EXPECT_EQ(board->getchecker(1, 3)->getColor(), 'B');
    EXPECT_EQ(board->getchecker(1, 2)->getColor(), '0');
    EXPECT_EQ(board->getchecker(6, 2)->getColor(), 'R');
    EXPECT_EQ(board->getchecker(6, 3)->getColor(), '0');
    EXPECT_EQ(board->getchecker(5, 5)->getColor(), 'R');
}
TEST(BoardTests, TestDestructor) {
    Board* board = new Board(8);
    board->~Board();
    EXPECT_TRUE(board->isDestroyed);
}
TEST(BoardTests, TestGetInstancesBlack) {
    Board* board = new Board(8);
    EXPECT_FLOAT_EQ(board->getInstances('B')[0]->getPosition().x, 0.0 );
    EXPECT_FLOAT_EQ(board->getInstances('B')[0]->getPosition().y, 0.0);

    EXPECT_FLOAT_EQ(board->getInstances('B')[1]->getPosition().x, 0.0);
    EXPECT_FLOAT_EQ(board->getInstances('B')[1]->getPosition().y, 2.0);
   
    EXPECT_FLOAT_EQ(board->getInstances('B')[2]->getPosition().x, 0.0);
    EXPECT_FLOAT_EQ(board->getInstances('B')[2]->getPosition().y, 4.0);
}
TEST(BoardTests, TestGetInstancesRed) {
    Board* board = new Board(8);
    EXPECT_FLOAT_EQ(board->getInstances('R')[0]->getPosition().x, 5.0);
    EXPECT_FLOAT_EQ(board->getInstances('R')[0]->getPosition().y, 1.0);

    EXPECT_FLOAT_EQ(board->getInstances('R')[1]->getPosition().x, 5.0);
    EXPECT_FLOAT_EQ(board->getInstances('R')[1]->getPosition().y, 3.0);

    EXPECT_FLOAT_EQ(board->getInstances('R')[2]->getPosition().x, 5.0);
    EXPECT_FLOAT_EQ(board->getInstances('R')[2]->getPosition().y, 5.0);
}
TEST(BoardTests, TestMoveIsAllowedRed)
{
    Board* board = new Board(8);
    EXPECT_TRUE(board->isAllowed(board->getchecker(5, 5)));
}
TEST(BoardTests, TestMoveIsAllowedBlack)
{
    Board* board = new Board(8);
    EXPECT_TRUE(!(board->isAllowed(board->getchecker(0, 2))));
}
TEST(BoardTests, TestSwapPieces)
{
    Board* board = new Board(8);
    Checker* check1 = new Checker(0, 0, 'B');
    Checker* check2 = new Checker(1, 0, 'R');
    board->swap(check1, check2,false);
    ASSERT_TRUE(check1->getPosition().x == 1);
    ASSERT_TRUE(check1->getPosition().y == 0);
}
TEST(BoardTests, TestCapturePiece)
{
    Board* board = new Board(8);
    Checker* check1 = new Checker(0, 0, 'B');
    Checker* check2 = new Checker(1, 0, 'R');
    board->capture(check1, check2);
    ASSERT_TRUE(check1->getPosition().x == 2);
    ASSERT_TRUE(check1->getPosition().y == 0);
}
TEST(BoardTests, TestGetTurn)
{
    Board* board = new Board(8);
    EXPECT_TRUE(board->getTurn() == 'R');
}
TEST(BoardTests, TestChangeTurn)
{
    Board* board = new Board(8);
    EXPECT_TRUE(board->getTurn() == 'R');
    board->changeTurn();
    ASSERT_TRUE(board->getTurn() == 'B');
}
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}