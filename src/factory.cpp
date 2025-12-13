#include "factory.hpp"

#include <sstream>


std::shared_ptr<NPC> NPCFactory::createNPC(const std::string &type, int x, int y) {
    if (type == "Squirrel" || type == "Belka") {
        return std::make_shared<Squirrel>(x, y);
    } else if (type == "Elf") {
        return std::make_shared<Elf>(x, y);
    } else if (type == "Bandit") {
        return std::make_shared<Bandit>(x, y);
    }
    return nullptr;
}

std::shared_ptr<NPC> NPCFactory::loadNPC(const std::string &line) {
    std::istringstream iss(line);
    std::string type;
    int x, y;
    if (iss >> type >> x >> y) {
        return createNPC(type, x, y);
    }
    return nullptr;
}
