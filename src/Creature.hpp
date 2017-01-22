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
	void attack();

private:
	enum class State {None, Idle, Decay, Run, Attack};

	friend std::ostream& operator<<(std::ostream& out, Creature::State state);

	void setState(State state);
	void updateState();
	void updateAnimation();


	ResAnim* animation {};
	State currentState {};
	spTween animationTween {};
	spTween positionTween {};
    spTextField nameBar {};
    spSprite sprite {};

};



using spCreature = oxygine::intrusive_ptr<Creature>;
