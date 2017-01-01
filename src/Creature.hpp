#pragma once
#include "oxygine-framework.h"
using oxygine::Sprite;
using oxygine::spSprite;
using oxygine::spTextField;
using oxygine::spTween;
using oxygine::Resources;
using oxygine::ResAnim;
using oxygine::Vector2;



class Creature: public Sprite {
public:
	Creature(Resources* resources);

	void moveTo(Vector2 position);

private:
	enum class Animation {Idle, Death, Run, Attack};
	void setAnimation(Animation animation);

	Resources* resources {};
	ResAnim* animation {};
	spTween animationTween {};
	spTween positionTween {};
    spTextField nameBar {};
    spSprite sprite {};

};



using spCreature = oxygine::intrusive_ptr<Creature>;
