#include <gtest/gtest.h>
#include "../include/npc.hpp"

TEST(NPC, Initialization) {
    {std::string name = "TestNPC";
    Elf npc(1, 1, name);

    EXPECT_EQ(npc.getName(), name);
    EXPECT_TRUE(npc.isAlive());
    EXPECT_TRUE(npc.getTypeStr() == "Elf");}

    {std::string name = "TestNPC";
    Bear npc(1, 1, name);

    EXPECT_EQ(npc.getName(), name);
    EXPECT_TRUE(npc.isAlive());
    EXPECT_TRUE(npc.getTypeStr() == "Bear");}

    {std::string name = "TestNPC";
    Thief npc(1, 1, name);

    EXPECT_EQ(npc.getName(), name);
    EXPECT_TRUE(npc.isAlive());
    EXPECT_TRUE(npc.getTypeStr() == "Thief");}
}
 
TEST(NPC, Roam) {
    std::string name = "TestNPC";
    Bear npc(1,1,name);

    int initialX = npc.x;
    int initialY = npc.y;

    npc.roam();

    EXPECT_TRUE(npc.x >= initialX - 1 && npc.x <= initialX + 1);
    EXPECT_TRUE(npc.y >= initialY - 1 && npc.y <= initialY + 1);
}

TEST(NPC, Die) {
    std::string name = "TestNPC";
    Bear npc(1,1,name);

    npc.die();

    EXPECT_FALSE(npc.isAlive());
}

TEST(NPC, Attack) {
    std::string attackerName = "AttackerNPC";
    Bear attacker(1,1,attackerName);

    std::string targetName = "TargetNPC";
    Elf target(3,3,targetName);

    attacker.attack(&target);

    EXPECT_FALSE(target.isAlive());
}

TEST(NPC, Serialization) {
    std::string name = "TestNPC";
    Elf npc(1,1,name);

    std::ostringstream oss;
    npc.serialize(oss);

    std::string expectedSerializedOutput = "0,TestNPC,1,1\n";
    EXPECT_EQ(oss.str(), expectedSerializedOutput);
}

TEST(NPC, GetDistance2) {
    std::string name1 = "TestNPC1";
    Thief npc1(0,0,name1);

    std::string name2 = "TestNPC2";
    Bear npc2(3,4,name2);

    int distanceSquared = npc1.getDistance2(&npc2);

    EXPECT_EQ(distanceSquared, 5);
}

TEST(NPC, TypeStr) {
    std::string name = "TestNPC";
    Elf npc(1,1,name);

    std::string typeStr = npc.getTypeStr();
    EXPECT_TRUE(typeStr == "Elf");
}

TEST(NPC, IsCompatibleWith) {
    std::string elfName = "ElfNPC";
    Elf elf(1,1,elfName);
    elf.setAttackRange(ELF_ATTACK_RANGE);

    std::string bearName = "BearNPC";
    Bear bear(1,1,bearName);
    bear.setAttackRange(BEAR_ATTACK_RANGE);

    std::string thiefName = "ThiefNPC";
    Thief thief(1,1,thiefName);
    thief.setAttackRange(THIEF_ATTACK_RANGE);

    EXPECT_FALSE(elf.isCompatibleWith(&elf));
    EXPECT_TRUE(elf.isCompatibleWith(&thief));
    EXPECT_FALSE(elf.isCompatibleWith(&bear));

    EXPECT_TRUE(bear.isCompatibleWith(&elf));
    EXPECT_FALSE(bear.isCompatibleWith(&thief));
    EXPECT_FALSE(bear.isCompatibleWith(&bear));

    EXPECT_FALSE(thief.isCompatibleWith(&elf));
    EXPECT_TRUE(thief.isCompatibleWith(&thief));
    EXPECT_FALSE(thief.isCompatibleWith(&bear));
}

TEST(NPC, DeserializationElf) {
    std::string elfSerialized = "0,ElfNPC,1,2\n";
    NPC* elf = deserialize(elfSerialized);

    EXPECT_NE(elf, nullptr);
    EXPECT_EQ(elf->getType(), ELF);
    EXPECT_EQ(elf->getName(), "ElfNPC");
    EXPECT_EQ(elf->x, 1);
    EXPECT_EQ(elf->y, 2);

    delete elf;
}

TEST(NPC, DeserializationBear) {
    std::string bearSerialized = "1,BearNPC,3,4\n";
    NPC* bear = deserialize(bearSerialized);

    EXPECT_NE(bear, nullptr);
    EXPECT_EQ(bear->getType(), BEAR);
    EXPECT_EQ(bear->getName(), "BearNPC");
    EXPECT_EQ(bear->x, 3);
    EXPECT_EQ(bear->y, 4);

    delete bear;
}

TEST(NPC, DeserializationThief) {
    std::string thiefSerialized = "2,ThiefNPC,5,6\n";
    NPC* thief = deserialize(thiefSerialized);

    EXPECT_NE(thief, nullptr);
    EXPECT_EQ(thief->getType(), THIEF);
    EXPECT_EQ(thief->getName(), "ThiefNPC");
    EXPECT_EQ(thief->x, 5);
    EXPECT_EQ(thief->y, 6);

    delete thief;
}

TEST(FactoryTest, Creation) {
    NPCFactory factory;
    std::string elfName = "ElfNPC";
    factory.createNPC(static_cast<NPCType>(0), 1, 1, elfName);
    factory.createNPC(static_cast<NPCType>(1), 1, 1, elfName);
    factory.createNPC(static_cast<NPCType>(2), 1, 1, elfName);
    
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
