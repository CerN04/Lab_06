#include "battle_visitor.hpp"

#include <memory>

#include "Bandit.hpp"
#include "common_visitor.hpp"
#include "Elf.hpp"
#include "NPC.hpp"
#include "Squirrel.hpp"

void BattleVisitor::visit(std::shared_ptr<Squirrel> belka, std::shared_ptr<NPC> other) {
    if (other->is_Squirrel()) {
        (*belka).fight(std::static_pointer_cast<Squirrel>(other));
    } else if (other->is_Elf()) {
        (*belka).fight(std::static_pointer_cast<Elf>(other));
    } else {
        (*belka).fight(std::static_pointer_cast<Bandit>(other));
    }
}

void BattleVisitor::visit(std::shared_ptr<Elf> elf, std::shared_ptr<NPC> other) {
    if (other->is_Squirrel()) {
        (*elf).fight(std::static_pointer_cast<Squirrel>(other));
    } else if (other->is_Elf()) {
        (*elf).fight(std::static_pointer_cast<Elf>(other));
    } else {
        (*elf).fight(std::static_pointer_cast<Bandit>(other));
    }
}

void BattleVisitor::visit(std::shared_ptr<Bandit> bandygan, std::shared_ptr<NPC> other) {
    if (other->is_Squirrel()) {
        (*bandygan).fight(std::static_pointer_cast<Squirrel>(other));
    } else if (other->is_Elf()) {
        (*bandygan).fight(std::static_pointer_cast<Elf>(other));
    } else {
        (*bandygan).fight(std::static_pointer_cast<Bandit>(other));
    }
}
