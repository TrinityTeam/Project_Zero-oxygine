#include "CreatureReader.hpp"
#include "ReadError.hpp"
#include <fstream>
#include <iostream>
#include <json/json.h>



spCreature CreatureReader::readFrom(const std::string& fileName, Resources* resources, const std::string& dataPath) {
    Json::CharReaderBuilder builder;
    builder["collectComments"] = false;
        
    auto filePath = dataPath+fileName;
    std::ifstream in(filePath);

    if(not in) {
        throw ReadError(filePath, "Input error; File might not exist");
    }

    Json::Value root;
    std::string errs {};
    bool ok = Json::parseFromStream(builder, in, &root, &errs);
    in.close();

    if(not ok) {
        throw ReadError(filePath, errs);
    }

    spCreature creature = new Creature(resources);
    const Json::Value& appearenceRoot  = root["appearence"];
    if(appearenceRoot.isNull()) {
        throw ReadError(filePath, "Node 'appearence' has not been found");
    }
    Creature::AnimationData data;
    if(not appearenceRoot["file"].isNull()) {
        data.file = appearenceRoot["file"].asString();
    } else {
        throw ReadError(filePath, "Node 'file' in 'appearence' has not been found");
    }
    
    auto animationsRoot = appearenceRoot.get("animations", Json::Value(Json::objectValue));
    for(auto it = animationsRoot.begin(); it != animationsRoot.end(); it++) {
        auto name = it.name();
        auto animation = *it;
        data.row = animation["row"].isNull() ? 1 : animation["row"].asInt();
        data.duration = animation["duration"].isNull() ? 600 : animation["duration"].asInt();
        data.framesNum = animation["frames_num"].isNull() ? 1 : animation["frames_num"].asInt();
        if(name == "Idle") {
            creature->setAnimation(Creature::State::Idle, data);

        } else if(name == "Run") {
            creature->setAnimation(Creature::State::Run, data);

        } else if(name == "Attack") {
            creature->setAnimation(Creature::State::Attack, data);

        } else if(name == "Decay") {
            creature->setAnimation(Creature::State::Decay, data);
        }
    }

    return creature;
}
