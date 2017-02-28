#include "SceneReader.hpp"
#include "CreatureReader.hpp"
#include "ReadError.hpp"
#include <fstream>
#include <json/json.h>
#include <iostream>



spScene SceneReader::readFrom(const std::string& fileName, Resources* resources, const std::string& dataPath) {
    Json::CharReaderBuilder builder;
    builder["collectComments"] = false;
    
    std::string filePath = dataPath+fileName;
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

    auto characterNode = root["character"];
    if(characterNode.isNull()) {
        throw ReadError(filePath, "Parsing error; 'character' node has not been found");
    }

    spScene scene = new Scene(resources);
    scene->setCharacter(CreatureReader::readFrom("creatures/"+characterNode["type"].asString()+".json", resources));
    scene->getCharacter()->setName(characterNode["name"].asString());
    scene->getCharacter()->setPosition(characterNode["position"]["x"].asInt(), 
                                       characterNode["position"]["y"].asInt());

    auto creaturesNode = root["creatures"];
    if(creaturesNode.isArray()) {
        for(const Json::Value& creatureNode: creaturesNode) {
            spCreature creature = CreatureReader::readFrom("creatures/"+creatureNode["type"].asString()+".json", resources);
            creature->setName(creatureNode["name"].asString());
            creature->setPosition(creatureNode["position"]["x"].asInt(), 
                                  creatureNode["position"]["y"].asInt());
            scene->addCreature(creature);
        }
    }

    return scene;
}