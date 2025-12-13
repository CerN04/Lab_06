#include "observers.hpp"

#include <iostream>


void ConsoleObserver::on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool res) {
    std::cout << "Fighting: ";
    attacker->print();
    std::cout << (res ? " wins " : " loses ");
    defender->print();
    std::cout << std::endl;
}

FileObserver::FileObserver() { file.open("log.txt", std::ios::app); }

FileObserver::~FileObserver() {
    if (file.is_open()) {
        file.close();
    }
}

void FileObserver::on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool res) {
    if (!file.is_open()) {
        throw std::runtime_error("File is not open");
    }
    file << "Fighting: Attacker - " << attacker->name << " on (" << attacker->x << ", " << attacker->y << ")";
    file << (res ? " wins " : " loses ");
    file << "Defender - " << defender->name << " on (" << defender->x << ", " << defender->y << ")\n";
    file.flush();
}

void DeathObserver::on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool res) {
    if (res) {
        dead_npcs.insert(defender);
    } else {
        dead_npcs.insert(attacker);
    }
}

void DeathObserver::clear() { dead_npcs.clear(); }