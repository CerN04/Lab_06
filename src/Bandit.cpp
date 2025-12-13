#include "Bandit.hpp"

#include <iostream>
#include <memory>
#include <ostream>

#include "common_visitor.hpp"
#include "Elf.hpp"
#include "NPC.hpp"
#include "Squirrel.hpp"


Bandit::Bandit(int x, int y) : NPC("Bandit", x, y) {}

Bandit::Bandit(std::istream &is) : NPC("Bandit", is) {}

bool Bandit::is_Bandit() const { return true; }

bool Bandit::fight(std::shared_ptr<Squirrel> other) {
    bool is_win = true;
    fight_note(other, is_win);
    return is_win;
}

bool Bandit::fight(std::shared_ptr<Elf> other) {
    bool is_win = false;
    fight_note(other, is_win);
    return is_win;
}

bool Bandit::fight(std::shared_ptr<Bandit> other) {
    bool is_win = rand() % 2;
    fight_note(other, is_win);
    return is_win;
}

void Bandit::accept(CommonVisitor &vis, std::shared_ptr<NPC> npc) {
    vis.visit(std::static_pointer_cast<Bandit>(std::enable_shared_from_this<NPC>::shared_from_this()), npc);
}

void Bandit::print() const { std::cout << "Bandit at (" << this->x << ", " << this->y << ")"; }

void Bandit::safe(std::ostream &os) const { os << "Bandit " << this->x << " " << this->y << "\n"; }
