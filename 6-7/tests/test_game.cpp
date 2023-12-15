#include <gtest/gtest.h>
#include <string>
#include "../include/npc.hpp"
#include "../include/game.hpp" 

std::string elfName = "testElf";
std::string bearName = "testBear";
std::string thiefName = "testThief";

Elf elf(1,1,elfName);
Bear bear(2,2,bearName);
Thief thief(3,3,thiefName);

TEST(GameTest, Initialization) {
    int width = 10;
    int height = 10;
    Game game(width, height);

    EXPECT_EQ(game.getWidth(), width);
    EXPECT_EQ(game.getHeight(), height);
    EXPECT_TRUE(game.isRunning());
    EXPECT_TRUE(game.isPaused());
}

TEST(GameTest, NPCAdditionAndRemoval) {
    Game game(10, 10);

    game.addNPC(&elf);
    game.addNPC(&bear);

    const std::vector<NPC*>& npcList = game.getNPCList();
    EXPECT_EQ(npcList.size(), 2);

    game.removeNPC(&elf);
    EXPECT_EQ(npcList.size(), 1);

}

TEST(GameTest, PlayerMovement) {
    Game game(10, 10);

    Player* player = new Player(5, 5);
    game.addPlayer(player);

    player->handleInput('w');
    EXPECT_EQ(player->y, 4);

    player->handleInput('s');
    EXPECT_EQ(player->y, 5);

    player->handleInput('a');
    EXPECT_EQ(player->x, 4);

    player->handleInput('d');
    EXPECT_EQ(player->x, 5);

}

TEST(GameTest, MapUpdateAndClear) {
    Game game(10, 10);

    game.addNPC(&elf);

    game.updateNPCs();
    EXPECT_EQ(game.getElement(elf.x, elf.y), ELF_CELL);

    game.clearMap();
    EXPECT_EQ(game.getElement(elf.x, elf.y), ELF_CELL);

}

TEST(GameTest, clearNPCs) {
    Game game(10, 10);

    game.addNPC(&elf);
    game.addNPC(&bear);
    game.addNPC(&thief);

    game.updateNPCs();
    EXPECT_EQ(game.getElement(elf.x, elf.y), ELF_CELL);
    EXPECT_EQ(game.getElement(bear.x, bear.y), BEAR_CELL);
    EXPECT_EQ(game.getElement(thief.x, thief.y), THIEF_CELL);

    game.clearNPCs();
    EXPECT_EQ(game.getElement(elf.x, elf.y), EMPTY_CELL);
    EXPECT_EQ(game.getElement(bear.x, bear.y), EMPTY_CELL);
    EXPECT_EQ(game.getElement(thief.x, thief.y), EMPTY_CELL);
}

TEST(GameTest, PauseAndResume) {
    Game game(10, 10);

    game.pause();
    EXPECT_TRUE(game.isPaused());

    game.resume();
    EXPECT_FALSE(game.isPaused());
}

TEST(GameTest, GetElement) {
    Game game(10, 10);
    game.setElement(1,1,'*');
    game.setElement(1,1,'.');

    EXPECT_EQ(game.getElement(1,1), '.');
    game.clearMap();
    EXPECT_EQ(game.getElement(1,1), EMPTY_CELL);
}

TEST(GameTest, SetElement) {
    Game game(10, 10);
    game.setElement(1,1,'*');

    EXPECT_EQ(game.getElement(1,1), '*');
}

TEST(GameTest, DrawLine) {
    Game game(10, 10);

    game.drawLine(0, 0, 9, 9, ATTACK_CELL);

    EXPECT_EQ(game.getElement(0, 0), ATTACK_CELL);
    EXPECT_EQ(game.getElement(9, 9), ATTACK_CELL);
    EXPECT_EQ(game.getElement(5, 5), ATTACK_CELL);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    int res = RUN_ALL_TESTS();
    return res;
}