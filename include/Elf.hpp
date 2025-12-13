#pragma once

#include <memory>
#include <strstream>

#include "NPC.hpp"


struct Elf : public NPC {
    Elf(int x, int y);
    Elf(std::istream &is);
    bool is_Elf() const override;

    virtual bool fight(std::shared_ptr<Squirrel> other) override;
    virtual bool fight(std::shared_ptr<Elf> other) override;
    virtual bool fight(std::shared_ptr<Bandit> other) override;

    void accept(CommonVisitor &vis, std::shared_ptr<NPC> other) override;
    void print() const override;
    void safe(std::ostream &os) const override;
};
