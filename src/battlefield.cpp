#include "battlefield.hpp"

#include <memory>
#include <vector>
#include <set>

#include "battle_visitor.hpp"


void Battlefield::add_npc(std::shared_ptr<NPC> new_npc) {
    nps_spis.insert(new_npc);
}

void Battlefield::delete_npc(std::shared_ptr<NPC> npc) {
    nps_spis.erase(npc);
}

void Battlefield::update_battlefield(size_t battle_range) {
    death_observer.clear();

    for (auto &npc : nps_spis) {
        npc->subscribe(std::shared_ptr<IFightObserver>(&death_observer, [](IFightObserver*){}));
    }

    auto alive_npcs = nps_spis;

    for (auto it1 = alive_npcs.begin(); it1 != alive_npcs.end(); ) {
        auto npc1 = *it1;
        bool npc1_removed = false;
        if (death_observer.dead_npcs.count(npc1)) {
            it1 = alive_npcs.erase(it1);
            continue;
        }
        for (auto it2 = std::next(it1); it2 != alive_npcs.end(); ) {
            auto npc2 = *it2;
            bool npc2_removed = false;
            if (death_observer.dead_npcs.count(npc2)) {
                it2 = alive_npcs.erase(it2);
                continue;
            }
            if (npc1->is_murder_range(npc2, battle_range)) {
                npc1->accept(visitor, npc2);

                if (death_observer.dead_npcs.count(npc1)) {
                    it1 = alive_npcs.erase(it1);
                    npc1_removed = true;
                    break;
                }
                if (death_observer.dead_npcs.count(npc2)) {
                    it2 = alive_npcs.erase(it2);
                    continue;
                } else {
                    ++it2;
                }
            } else {
                ++it2;
            }
        }

        if (!npc1_removed) {
            ++it1;
        }
    }
    nps_spis = alive_npcs;
}