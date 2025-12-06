#pragma once

#include <future>
#include <memory>


struct NPC;
struct Squirrel;
struct Elf;
struct Bandit;

struct CommonVisitor {
    virtual ~CommonVisitor() = default;
    virtual void visit(std::shared_ptr<Squirrel> belka, std::shared_ptr<NPC> other) = 0;
    virtual void visit(std::shared_ptr<Elf> elf, std::shared_ptr<NPC> other) = 0;
    virtual void visit(std::shared_ptr<Bandit> bandygan, std::shared_ptr<NPC> other) = 0;
};