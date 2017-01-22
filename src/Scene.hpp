#pragma once
#include "oxygine-framework.h"
#include "Creature.hpp"
using oxygine::Actor;
using oxygine::Vector2;
using oxygine::Event;
using oxygine::Resources;



class Scene: public Actor {
public:
    Scene(Resources* resources);

private:
    void buttonClicked(Event* event);
    void keyReleased(Event* event);
    void runSprite(Vector2 destination);

	Resources* resources {};
	spCreature character {};
};



using spScene = oxygine::intrusive_ptr<Scene>;
