#pragma once

#include <memory>
#include <strstream>

#include "NPC.hpp"


struct Bandit : public NPC {
    Bandit(int x, int y);
    Bandit(std::istream &is);
    bool is_Bandit() const override;

    virtual bool fight(std::shared_ptr<Squirrel> other) override;
    virtual bool fight(std::shared_ptr<Elf> other) override;
    virtual bool fight(std::shared_ptr<Bandit> other) override;

    void accept(CommonVisitor &vis, std::shared_ptr<NPC> other) override;
    void print() const override;
    void safe(std::ostream &os) const override;
};
