#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <vector>

#include "Bandit.hpp"
#include "battlefield.hpp"
#include "Elf.hpp"
#include "factory.hpp"
#include "NPC.hpp"
#include "observers.hpp"
#include "Squirrel.hpp"


void save(const NPCSet &array, const std::string &filename) {
    std::ofstream fs(filename);
    for (auto &n : array)
        n->safe(fs);
    fs.flush();
    fs.close();
}

NPCSet load(const std::string &filename) {
    NPCSet result;
    std::ifstream is(filename);
    if (is.good() && is.is_open()) {
        std::string line;
        while (std::getline(is, line)) {
            if (!line.empty()) {
                auto npc = NPCFactory::loadNPC(line);
                if (npc) {
                    result.insert(npc);
                }
            }
        }
        is.close();
    } else
        std::cerr << "Error opening file: " << filename << std::endl;
    return result;
}

std::ostream &operator<<(std::ostream &os, const NPCSet &array) {
    for (auto &n : array) {
        os << *n << std::endl;
    }
    return os;
}

int main() {
    Battlefield battlefield;
    auto console_obs = std::make_shared<ConsoleObserver>();
    auto file_obs = std::make_shared<FileObserver>();

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::cout << "Generating ..." << std::endl;
    for (size_t i = 0; i < 100; ++i) {
        std::string types[] = {"Squirrel", "Elf", "Bandit"};
        std::string type = types[std::rand() % 3];
        int x = std::rand() % 501;
        int y = std::rand() % 501;

        auto npc = NPCFactory::createNPC(type, x, y);
        if (npc) {
            npc->subscribe(console_obs);
            battlefield.add_npc(npc);
        }
    }

    std::cout << "Saving ..." << std::endl;
    save(battlefield.nps_spis, "log.txt");

    std::cout << "Loading ..." << std::endl;
    battlefield.nps_spis = load("log.txt");

    for (auto &npc : battlefield.nps_spis) {
        npc->subscribe(console_obs);
        npc->subscribe(file_obs);
    }

    std::cout << "Fighting ..." << std::endl << "Initial NPCs: " << battlefield.nps_spis.size() << std::endl;

    for (size_t distance = 20; (distance <= 100) && !battlefield.nps_spis.empty(); distance += 10) {
        size_t before = battlefield.nps_spis.size();
        battlefield.update_battlefield(distance);
        size_t killed = before - battlefield.nps_spis.size();

        std::cout << "\nFight stats ----------" << std::endl
                  << "Distance: " << distance << std::endl
                  << "Killed: " << killed << std::endl
                  << "Remaining: " << battlefield.nps_spis.size() << std::endl;
    }

    std::cout << "\nSurvivors:" << std::endl;
    std::cout << battlefield.nps_spis;

    std::ofstream log_file("log.txt", std::ios::app);
    if (log_file.is_open()) {
        log_file << "\n=== BATTLE RESULTS ===" << std::endl;
        log_file << "Total survivors: " << battlefield.nps_spis.size() << std::endl;
        log_file << "Total killed: " << (100 - battlefield.nps_spis.size()) << std::endl;
        log_file << "\nSurvivors list:" << std::endl;
        for (auto &n : battlefield.nps_spis) {
            n->safe(log_file);
        }
        log_file.close();
    }

    return 0;
}