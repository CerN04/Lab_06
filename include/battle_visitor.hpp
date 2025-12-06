#pragma once

#include "common_visitor.hpp"

struct BattleVisitor : public CommonVisitor {
    virtual void visit(std::shared_ptr<Squirrel> belka, std::shared_ptr<NPC> other) override;
    virtual void visit(std::shared_ptr<Elf> elf, std::shared_ptr<NPC> other) override;
    virtual void visit(std::shared_ptr<Bandit> bandygan, std::shared_ptr<NPC> other) override;
};
