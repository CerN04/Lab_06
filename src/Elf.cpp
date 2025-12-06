#include "Elf.hpp"

#include <iostream>
#include <memory>
#include <ostream>

#include "Bandit.hpp"
#include "common_visitor.hpp"
#include "NPC.hpp"
#include "Squirrel.hpp"


Elf::Elf(int x, int y) : NPC("Elf", x, y) {}

Elf::Elf(std::istream &is) : NPC("Elf", is) {}

bool Elf::is_Elf() const { return true; }

bool Elf::fight(std::shared_ptr<Squirrel> other) {
    bool is_win = false;
    fight_note(other, is_win);
    return is_win;
}

bool Elf::fight(std::shared_ptr<Elf> other) {
    bool is_win = rand() % 2;
    fight_note(other, is_win);
    return is_win;
}

bool Elf::fight(std::shared_ptr<Bandit> other) {
    bool is_win = true;
    fight_note(other, is_win);
    return is_win;
}

void Elf::accept(CommonVisitor &vis, std::shared_ptr<NPC> npc) {
    vis.visit(std::static_pointer_cast<Elf>(std::enable_shared_from_this<NPC>::shared_from_this()), npc);
}

void Elf::print() const { std::cout << "Elf at (" << this->x << ", " << this->y << ")"; }

void Elf::safe(std::ostream &os) const { os << "Elf " << this->x << " " << this->y << "\n"; }
