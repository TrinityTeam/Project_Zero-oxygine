#pragma once
#include <set>
#include "oxygine-framework.h"
#include "Creature.hpp"
using oxygine::Actor;
using oxygine::Vector2;
using oxygine::Event;
using oxygine::Resources;



class Scene: public Actor {
public:
    Scene(Resources* resources);

    void addCreature(spCreature creature);
    Creature* getCharacter();
    void setCharacter(spCreature character);

private:
    void buttonClicked(Event* event);
    void keyReleased(Event* event);
    void runSprite(Vector2 destination);

	Resources* resources {};
	spCreature character {};
    std::set<spCreature> creatures {};
};



using spScene = oxygine::intrusive_ptr<Scene>;
