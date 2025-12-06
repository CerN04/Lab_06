#pragma once

#include <fstream>
#include <memory>
#include <string>

#include "Bandit.hpp"
#include "Elf.hpp"
#include "NPC.hpp"
#include "Squirrel.hpp"


struct NPCFactory {
    static std::shared_ptr<NPC> createNPC(const std::string &type, int x, int y);
    static std::shared_ptr<NPC> loadNPC(const std::string &line);
};
