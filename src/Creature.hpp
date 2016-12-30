#pragma once
#include "oxygine-framework.h"
using oxygine::Sprite;
using oxygine::spSprite;
using oxygine::spTextField;
using oxygine::Resources;
using oxygine::Vector2;



class Creature: public Sprite {
public:
	Creature(Resources* resources);

	void moveTo(Vector2 position);

private:
	Resources* resources {};
    spTextField nameBar {};
    spSprite sprite {};

};



using spCreature = oxygine::intrusive_ptr<Creature>;
