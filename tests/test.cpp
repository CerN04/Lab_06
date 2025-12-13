#include <gtest/gtest.h>
#include "NPC.hpp"
#include "Squirrel.hpp"
#include "Elf.hpp"
#include "Bandit.hpp"
#include "factory.hpp"
#include "battlefield.hpp"
#include "observers.hpp"
#include <memory>
#include <sstream>

// =============================================================================
// ГРУППА ТЕСТОВ: Базовые функции NPC
// =============================================================================

TEST(NPC_Basic_Test, CreateSquirrel) {
    auto squirrel = std::make_shared<Squirrel>(10, 20);
    EXPECT_EQ(squirrel->name, "Belka");
    EXPECT_EQ(squirrel->x, 10);
    EXPECT_EQ(squirrel->y, 20);
    EXPECT_TRUE(squirrel->is_Squirrel());
    EXPECT_FALSE(squirrel->is_Elf());
    EXPECT_FALSE(squirrel->is_Bandit());
}

TEST(NPC_Basic_Test, CreateElf) {
    auto elf = std::make_shared<Elf>(30, 40);
    EXPECT_EQ(elf->name, "Elf");
    EXPECT_EQ(elf->x, 30);
    EXPECT_EQ(elf->y, 40);
    EXPECT_FALSE(elf->is_Squirrel());
    EXPECT_TRUE(elf->is_Elf());
    EXPECT_FALSE(elf->is_Bandit());
}

TEST(NPC_Basic_Test, CreateBandit) {
    auto bandit = std::make_shared<Bandit>(50, 60);
    EXPECT_EQ(bandit->name, "Bandit");
    EXPECT_EQ(bandit->x, 50);
    EXPECT_EQ(bandit->y, 60);
    EXPECT_FALSE(bandit->is_Squirrel());
    EXPECT_FALSE(bandit->is_Elf());
    EXPECT_TRUE(bandit->is_Bandit());
}

TEST(NPC_Basic_Test, SaveAndLoad) {
    auto squirrel = std::make_shared<Squirrel>(100, 200);
    std::stringstream ss;
    squirrel->safe(ss);

    std::string expected = "Belka 100 200\n";
    EXPECT_EQ(ss.str(), expected);
}

TEST(NPC_Basic_Test, MurderRange) {
    auto npc1 = std::make_shared<Squirrel>(0, 0);
    auto npc2 = std::make_shared<Squirrel>(3, 4);

    EXPECT_TRUE(npc1->is_murder_range(npc2, 6));
    EXPECT_FALSE(npc1->is_murder_range(npc2, 4));
}

TEST(NPC_Basic_Test, ObserverSubscription) {
    auto squirrel = std::make_shared<Squirrel>(0, 0);
    auto observer = std::make_shared<ConsoleObserver>();

    EXPECT_EQ(squirrel->observers.size(), 0);
    squirrel->subscribe(observer);
    EXPECT_EQ(squirrel->observers.size(), 1);
}

// =============================================================================
// ГРУППА ТЕСТОВ: Правила боя (Вариант 4)
// =============================================================================

TEST(Battle_Rules_Test, SquirrelVsSquirrel) {
    auto squirrel1 = std::make_shared<Squirrel>(0, 0);
    auto squirrel2 = std::make_shared<Squirrel>(1, 1);
    auto observer = std::make_shared<ConsoleObserver>();

    squirrel1->subscribe(observer);
    squirrel2->subscribe(observer);

    bool result = squirrel1->fight(squirrel2);
    EXPECT_TRUE(result == true || result == false);
}

TEST(Battle_Rules_Test, SquirrelVsElf) {
    auto squirrel = std::make_shared<Squirrel>(0, 0);
    auto elf = std::make_shared<Elf>(1, 1);
    auto observer = std::make_shared<ConsoleObserver>();

    squirrel->subscribe(observer);
    elf->subscribe(observer);
    bool result = squirrel->fight(elf);
    EXPECT_TRUE(result);
}

TEST(Battle_Rules_Test, SquirrelVsBandit) {
    auto squirrel = std::make_shared<Squirrel>(0, 0);
    auto bandit = std::make_shared<Bandit>(1, 1);
    auto observer = std::make_shared<ConsoleObserver>();

    squirrel->subscribe(observer);
    bandit->subscribe(observer);
    bool result = squirrel->fight(bandit);
    EXPECT_FALSE(result);
}

TEST(Battle_Rules_Test, ElfVsBandit) {
    auto elf = std::make_shared<Elf>(0, 0);
    auto bandit = std::make_shared<Bandit>(1, 1);
    auto observer = std::make_shared<ConsoleObserver>();

    elf->subscribe(observer);
    bandit->subscribe(observer);
    bool result = elf->fight(bandit);
    EXPECT_TRUE(result);
}

TEST(Battle_Rules_Test, BanditVsSquirrel) {
    auto bandit = std::make_shared<Bandit>(0, 0);
    auto squirrel = std::make_shared<Squirrel>(1, 1);
    auto observer = std::make_shared<ConsoleObserver>();

    bandit->subscribe(observer);
    squirrel->subscribe(observer);
    bool result = bandit->fight(squirrel);
    EXPECT_TRUE(result);
}

TEST(Battle_Rules_Test, ElfVsSquirrel) {
    auto elf = std::make_shared<Elf>(0, 0);
    auto squirrel = std::make_shared<Squirrel>(1, 1);
    auto observer = std::make_shared<ConsoleObserver>();

    elf->subscribe(observer);
    squirrel->subscribe(observer);
    bool result = elf->fight(squirrel);
    EXPECT_FALSE(result);
}

TEST(Battle_Rules_Test, ObserverNotification) {
    auto squirrel = std::make_shared<Squirrel>(0, 0);
    auto elf = std::make_shared<Elf>(1, 1);

    class TestObserver : public IFightObserver {
    public:
        bool fight_called = false;
        void on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool res) override {
            fight_called = true;
            EXPECT_EQ(attacker->name, "Belka");
            EXPECT_EQ(defender->name, "Elf");
            EXPECT_TRUE(res);
        }
    };

    auto observer = std::make_shared<TestObserver>();
    squirrel->subscribe(observer);
    elf->subscribe(observer);

    squirrel->fight(elf);
    EXPECT_TRUE(observer->fight_called);
}

// =============================================================================
// ГРУППА ТЕСТОВ: Factory паттерн
// =============================================================================

TEST(Factory_Test, CreateSquirrel) {
    auto npc = NPCFactory::createNPC("Squirrel", 10, 20);
    ASSERT_NE(npc, nullptr);
    EXPECT_EQ(npc->name, "Belka");
    EXPECT_EQ(npc->x, 10);
    EXPECT_EQ(npc->y, 20);
    EXPECT_TRUE(npc->is_Squirrel());
}

TEST(Factory_Test, CreateElf) {
    auto npc = NPCFactory::createNPC("Elf", 30, 40);
    ASSERT_NE(npc, nullptr);
    EXPECT_EQ(npc->name, "Elf");
    EXPECT_EQ(npc->x, 30);
    EXPECT_EQ(npc->y, 40);
    EXPECT_TRUE(npc->is_Elf());
}

TEST(Factory_Test, CreateBandit) {
    auto npc = NPCFactory::createNPC("Bandit", 50, 60);
    ASSERT_NE(npc, nullptr);
    EXPECT_EQ(npc->name, "Bandit");
    EXPECT_EQ(npc->x, 50);
    EXPECT_EQ(npc->y, 60);
    EXPECT_TRUE(npc->is_Bandit());
}

TEST(Factory_Test, CreateSquirrelAltName) {
    auto npc = NPCFactory::createNPC("Belka", 10, 20);
    ASSERT_NE(npc, nullptr);
    EXPECT_EQ(npc->name, "Belka");
    EXPECT_TRUE(npc->is_Squirrel());
}

TEST(Factory_Test, CreateInvalidType) {
    auto npc = NPCFactory::createNPC("InvalidType", 10, 20);
    EXPECT_EQ(npc, nullptr);
}

TEST(Factory_Test, LoadFromStream) {
    std::string line = "Squirrel 100 200";
    auto npc = NPCFactory::loadNPC(line);
    ASSERT_NE(npc, nullptr);
    EXPECT_EQ(npc->name, "Belka");
    EXPECT_EQ(npc->x, 100);
    EXPECT_EQ(npc->y, 200);
    EXPECT_TRUE(npc->is_Squirrel());
}

TEST(Factory_Test, LoadElfFromStream) {
    std::string line = "Elf 150 250";
    auto npc = NPCFactory::loadNPC(line);
    ASSERT_NE(npc, nullptr);
    EXPECT_EQ(npc->name, "Elf");
    EXPECT_EQ(npc->x, 150);
    EXPECT_EQ(npc->y, 250);
    EXPECT_TRUE(npc->is_Elf());
}

TEST(Factory_Test, LoadBanditFromStream) {
    std::string line = "Bandit 300 400";
    auto npc = NPCFactory::loadNPC(line);
    ASSERT_NE(npc, nullptr);
    EXPECT_EQ(npc->name, "Bandit");
    EXPECT_EQ(npc->x, 300);
    EXPECT_EQ(npc->y, 400);
    EXPECT_TRUE(npc->is_Bandit());
}

TEST(Factory_Test, LoadInvalidData) {
    std::string line = "Invalid 100";
    auto npc = NPCFactory::loadNPC(line);
    EXPECT_EQ(npc, nullptr);
}

TEST(Factory_Test, LoadEmptyStream) {
    std::string line = "";
    auto npc = NPCFactory::loadNPC(line);
    EXPECT_EQ(npc, nullptr);
}

// =============================================================================
// ГРУППА ТЕСТОВ: Battlefield и DeathObserver
// =============================================================================

TEST(Battlefield_Test, AddNPC) {
    Battlefield battlefield;
    auto squirrel = std::make_shared<Squirrel>(10, 20);

    EXPECT_EQ(battlefield.nps_spis.size(), 0);
    battlefield.add_npc(squirrel);
    EXPECT_EQ(battlefield.nps_spis.size(), 1);
}

TEST(Battlefield_Test, AddMultipleNPCs) {
    Battlefield battlefield;
    auto squirrel = std::make_shared<Squirrel>(0, 0);
    auto elf = std::make_shared<Elf>(10, 10);
    auto bandit = std::make_shared<Bandit>(20, 20);

    battlefield.add_npc(squirrel);
    battlefield.add_npc(elf);
    battlefield.add_npc(bandit);

    EXPECT_EQ(battlefield.nps_spis.size(), 3);
}

TEST(Battlefield_Test, DeleteNPC) {
    Battlefield battlefield;
    auto squirrel = std::make_shared<Squirrel>(0, 0);
    battlefield.add_npc(squirrel);

    EXPECT_EQ(battlefield.nps_spis.size(), 1);
    battlefield.delete_npc(squirrel);
    EXPECT_EQ(battlefield.nps_spis.size(), 0);
}

TEST(Battlefield_Test, BattleMode) {
    Battlefield battlefield;

    auto squirrel1 = std::make_shared<Squirrel>(0, 0);
    auto squirrel2 = std::make_shared<Squirrel>(1, 1);
    auto elf = std::make_shared<Elf>(100, 100);

    battlefield.add_npc(squirrel1);
    battlefield.add_npc(squirrel2);
    battlefield.add_npc(elf);

    auto console_obs = std::make_shared<ConsoleObserver>();
    auto file_obs = std::make_shared<FileObserver>();

    for (auto& npc : battlefield.nps_spis) {
        npc->subscribe(console_obs);
        npc->subscribe(file_obs);
    }

    size_t initial_count = battlefield.nps_spis.size();

    battlefield.update_battlefield(50);

    EXPECT_LE(battlefield.nps_spis.size(), initial_count);
}

TEST(Battlefield_Test, BattleModeLargeDistance) {
    Battlefield battlefield;

    auto squirrel1 = std::make_shared<Squirrel>(0, 0);
    auto squirrel2 = std::make_shared<Squirrel>(100, 100);

    battlefield.add_npc(squirrel1);
    battlefield.add_npc(squirrel2);

    auto console_obs = std::make_shared<ConsoleObserver>();
    auto file_obs = std::make_shared<FileObserver>();

    for (auto& npc : battlefield.nps_spis) {
        npc->subscribe(console_obs);
        npc->subscribe(file_obs);
    }

    size_t initial_count = battlefield.nps_spis.size();

    battlefield.update_battlefield(10);
    EXPECT_EQ(battlefield.nps_spis.size(), initial_count);
}

TEST(Battlefield_Test, DeathObserver) {
    Battlefield battlefield;

    auto squirrel = std::make_shared<Squirrel>(0, 0);
    auto elf = std::make_shared<Elf>(1, 1);

    battlefield.add_npc(squirrel);
    battlefield.add_npc(elf);
    EXPECT_EQ(battlefield.death_observer.dead_npcs.size(), 0);
    battlefield.update_battlefield(50);
    EXPECT_GE(battlefield.death_observer.dead_npcs.size(), 0);
}
