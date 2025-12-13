#pragma once

#include <future>
#include <memory>
#include <vector>


struct NPC;
struct Squirrel;
struct Elf;
struct Bandit;
struct CommonVisitor;

struct IFightObserver {
    virtual void on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool res) = 0;
};

struct NPC : public std::enable_shared_from_this<NPC> {
    std::string name;
    int x = 0;
    int y = 0;
    std::vector<std::shared_ptr<IFightObserver>> observers;
    NPC(const std::string &name, int &x, int &y);
    NPC(const std::string &name, std::istream &is);
    virtual ~NPC();
    void subscribe(std::shared_ptr<IFightObserver> observer);
    void fight_note(const std::shared_ptr<NPC> defender, bool res);
    bool is_murder_range(const std::shared_ptr<NPC> &other, size_t dist) const;

    virtual bool is_Squirrel() const;
    virtual bool is_Elf() const;
    virtual bool is_Bandit() const;
    virtual bool fight(std::shared_ptr<Squirrel> other) = 0;
    virtual bool fight(std::shared_ptr<Elf> other) = 0;
    virtual bool fight(std::shared_ptr<Bandit> other) = 0;
    virtual void accept(CommonVisitor &vis, std::shared_ptr<NPC> other) = 0;
    virtual void print() const = 0;
    virtual void safe(std::ostream &os) const = 0;
    friend std::ostream &operator<<(std::ostream &os, const NPC &npc);
};