#pragma once

#include <fstream>
#include <memory>
#include <set>

#include "NPC.hpp"


struct ConsoleObserver : public IFightObserver {
    void on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool res) override;
};

struct FileObserver : public IFightObserver {
    std::ofstream file;
    FileObserver();
    FileObserver(const FileObserver &) = delete;
    FileObserver &operator=(const FileObserver &) = delete;
    ~FileObserver();
    void on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool res) override;
};

struct DeathObserver : public IFightObserver {
    std::set<std::shared_ptr<NPC>> dead_npcs;
    void on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool res) override;
    void clear();
};