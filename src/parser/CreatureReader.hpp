#pragma once
#include "../Creature.hpp"
#include "ReadError.hpp"



class CreatureReader {
public:
    CreatureReader() = delete;
    CreatureReader(const CreatureReader&) = delete;

    static spCreature readFrom(const std::string& fileName, Resources* resources, const std::string& dataPath = "");

private:
    

};
