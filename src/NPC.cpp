#include "NPC.hpp"

#include <iostream>
#include <sstream>


NPC::NPC(const std::string &name, int &x, int &y) : name(name), x(x), y(y) {}

NPC::NPC(const std::string &name, std::istream &is) : name(name) { is >> x >> y; }

NPC::~NPC() {}

void NPC::subscribe(std::shared_ptr<IFightObserver> observer) { observers.push_back(observer); }

void NPC::fight_note(const std::shared_ptr<NPC> defender, bool res) {
    for (auto &observer : observers) {
        observer->on_fight(shared_from_this(), defender, res);
    }
}

bool NPC::is_murder_range(const std::shared_ptr<NPC> &other, size_t dist) const {
    int dx = x - other->x;
    int dy = y - other->y;
    return dx * dx + dy * dy <= dist * dist;
}

bool NPC::is_Squirrel() const { return false; }

bool NPC::is_Elf() const { return false; }

bool NPC::is_Bandit() const { return false; }

std::ostream &operator<<(std::ostream &os, const NPC &npc) {
    npc.print();
    return os;
}
