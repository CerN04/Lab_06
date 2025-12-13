#pragma once

#include <memory>
#include <set>

#include "battle_visitor.hpp"
#include "NPC.hpp"
#include "observers.hpp"


struct SharedPtrLess {
    bool operator()(const std::shared_ptr<NPC> &a, const std::shared_ptr<NPC> &b) const { return a.get() < b.get(); }
};

using NPCSet = std::set<std::shared_ptr<NPC>, SharedPtrLess>;

struct Battlefield {
    NPCSet nps_spis;
    DeathObserver death_observer;
    void add_npc(std::shared_ptr<NPC> npc);
    void delete_npc(std::shared_ptr<NPC> npc);
    void update_battlefield(size_t battle_range);

private:
    BattleVisitor visitor;
};