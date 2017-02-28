#pragma once
#include "../Scene.hpp"



class SceneReader {
public:
    SceneReader() = delete;
    SceneReader(const SceneReader&) = delete;

    static spScene readFrom(const std::string& fileName, Resources* resources, const std::string& dataPath = "");

private:


};

