#pragma once
#include "oxygine-framework.h"
#include "Creature.hpp"
using oxygine::Actor;
using oxygine::Vector2;
using oxygine::Event;
using oxygine::Resources;



class MainActor: public Actor {
public:
    MainActor(Resources* resources);

private:
    void buttonClicked(Event* event);
    void runSprite(Vector2 destination);

	Resources* resources {};
	spCreature character {};
};



using spMainActor = oxygine::intrusive_ptr<MainActor>;
