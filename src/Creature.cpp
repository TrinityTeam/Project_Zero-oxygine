#include "Creature.hpp"
#include <iostream>
using oxygine::TextStyle;
using oxygine::Color;
using oxygine::TextField;
using oxygine::Event;
using oxygine::Tween;
using oxygine::TweenQueue;
using oxygine::TweenDummy;



std::ostream& operator<<(std::ostream& out, Creature::State state) {
	using State = Creature::State;
	switch(state) {
	case State::Idle:
		out << "Idle";
		break;
	case State::Run:
		out << "Run";
		break;
	case State::Attack:
		out << "Attack";
		break;
	case State::Decay:
		out << "Decay";
		break;
	}
	return out;
}



Creature::Creature(Resources* resources):
	currentState {State::None},
	resources {resources},
	positionTween {new Tween},
	sprite {new Sprite} {

	setAnchor({0.5, 0.5});
	sprite->setAnchor({0.5, 0.5});
    addChild(sprite);
    
	updateState();

	initNameLabel("_anonymous");
}



void Creature::moveTo(Vector2 destination) {
	int direction = (destination.x > getPosition().x) ? 1 : -1; 
	sprite->setScaleX(direction);

	auto distance = getPosition().distance(destination);
	constexpr auto SPEED = 100.;

	// removing old tween(queue)
	{
	auto tween = getTween("tween position");
	if(tween) tween->remove();
	}

	positionTween = createTween(Sprite::TweenPosition(destination), (distance/SPEED)*1000., 1);
	// Queue is needed, because when tween calls its done callback, the tween's status is not 'done' 
	auto tween = addTween(TweenQueue::create(positionTween));
	tween->setName("tween position");
	tween->setDoneCallback([this](Event*) {
		updateState();
	});
	setState(State::Run);
}



void Creature::attack() {
	setState(State::Attack);
}



void Creature::setName(const std::string& name) {
    nameBar->setText(name);
}



void Creature::setAnimation(State state, AnimationData animation) {
	animationData[state] = animation;
	updateAnimation();
}



void Creature::initNameLabel(const std::string& name) {
	if(nameBar) {
		nameBar->detach();
	}
	nameBar = new TextField;
    nameBar->attachTo(this);
    TextStyle style;
    style.font = resources->getResFont("main");
    style.color = Color::White;
    style.vAlign = TextStyle::VALIGN_MIDDLE;
    style.hAlign = TextStyle::HALIGN_CENTER;
    nameBar->setStyle(style);
    nameBar->setText(name);
	nameBar->setY(-sprite->getSize().y/2-nameBar->getSize().y);
}



void Creature::setState(State state) {
	if(currentState != state) {
		currentState = state;
		updateAnimation();
	}
}



void Creature::updateState() {
	auto state = currentState;
	if((currentState == State::Attack and animationTween->isDone()) or
	   (currentState == State::Run and positionTween->isDone())) {
		currentState = State::None;
	}

	if(currentState == State::None) {
		if(positionTween->isStarted() and not positionTween->isDone()) {
			currentState = State::Run;
		} else {
			currentState = State::Idle;
		}
	}

	if(currentState != state) {
		updateAnimation();
	}
}



void Creature::updateAnimation() {
	AnimationData currentAnimationData;
	try {
		currentAnimationData = animationData.at(currentState);
	
	} catch (std::out_of_range) {
		std::cerr << "Animation for state " << currentState << " has not been specified\n";
		return;
	}
	auto animation = resources->getResAnim(currentAnimationData.file);

	if(animationTween) {
		animationTween->complete();
		animationTween->remove();
	}

	auto tween = Sprite::TweenAnim(animation, currentAnimationData.row);
	tween.setInterval(0, currentAnimationData.framesNum);

	switch(currentState) {
	case State::Idle: {
		animationTween = sprite->addTween(tween, currentAnimationData.duration, -1);
		break;
	}
	case State::Run: {
		animationTween = sprite->addTween(tween, currentAnimationData.duration, -1);
		break;
	}
	case State::Attack: {
		animationTween = createTween(tween, currentAnimationData.duration, 1);
		sprite->addTween(TweenQueue::create(animationTween))->
			setDoneCallback([this](Event*) {
				updateState();
			});
		break;
	}
	case State::Decay: {
		animationTween = sprite->addTween(tween, currentAnimationData.duration, 1);
		break;
	}
	}
}
