#pragma once
#include "oxygine-framework.h"
#include <map>
using oxygine::Sprite;
using oxygine::spSprite;
using oxygine::spTextField;
using oxygine::spTween;
using oxygine::Resources;
using oxygine::ResAnim;
using oxygine::Vector2;



class Creature: public Sprite {
public:
	enum class State {None, Idle, Decay, Run, Attack};

	struct AnimationData { std::string file; uint32_t row, framesNum; int32_t duration; };
	
public:
	Creature(Resources* resources);
	virtual ~Creature() { oxygine::log::warning("Destoyed");}

	void moveTo(Vector2 position);
	void attack();

	void setName(const std::string& name);

	void setAnimation(State state, AnimationData animation);


private:
	friend std::ostream& operator<<(std::ostream& out, Creature::State state);

	void initNameLabel(const std::string& name);
	void setState(State state);
	void updateState();
	void updateAnimation();

	std::map<State, AnimationData> animationData;
	Resources* resources {};
	State currentState {};
	spTween animationTween {};
	spTween positionTween {};
    spTextField nameBar {};
    spSprite sprite {};

};



using spCreature = oxygine::intrusive_ptr<Creature>;
