#include "Squirrel.hpp"

#include <iostream>
#include <memory>
#include <ostream>

#include "Bandit.hpp"
#include "common_visitor.hpp"
#include "Elf.hpp"
#include "NPC.hpp"

Squirrel::Squirrel(int x, int y) : NPC("Belka", x, y) {}

Squirrel::Squirrel(std::istream &is) : NPC("Belka", is) {}

bool Squirrel::is_Squirrel() const { return true; }

bool Squirrel::fight(std::shared_ptr<Squirrel> other) {
    bool is_win = rand() % 2;
    fight_note(other, is_win);
    return is_win;
}

bool Squirrel::fight(std::shared_ptr<Elf> other) {
    bool is_win = true;
    fight_note(other, is_win);
    return is_win;
}

bool Squirrel::fight(std::shared_ptr<Bandit> other) {
    bool is_win = false;
    fight_note(other, is_win);
    return is_win;
}

void Squirrel::accept(CommonVisitor &vis, std::shared_ptr<NPC> npc) {
    vis.visit(std::static_pointer_cast<Squirrel>(std::enable_shared_from_this<NPC>::shared_from_this()), npc);
}

void Squirrel::print() const { std::cout << "Belka at (" << this->x << " " << this->y << ")"; }

void Squirrel::safe(std::ostream &os) const { os << "Belka " << this->x << " " << this->y << "\n"; }