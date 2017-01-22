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
	animation {resources->getResAnim("General Zirix Starstrider")},
	positionTween {new Tween},
	sprite {new Sprite},
	nameBar {new TextField} {

	setAnchor({0.5, 0.5});
	sprite->setAnchor({0.5, 0.5});
    addChild(sprite);
    
	updateState();

    nameBar->attachTo(this);
    TextStyle style;
    style.font = resources->getResFont("main");
    style.color = Color::White;
    style.vAlign = TextStyle::VALIGN_MIDDLE;
    style.hAlign = TextStyle::HALIGN_CENTER;
    nameBar->setStyle(style);
    nameBar->setText("Anonymous");
	nameBar->setY(-sprite->getSize().y/2-nameBar->getSize().y);
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
	// Queue is needed because when a tween calls its done callback, its status is not 'done' 
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



void Creature::setState(State state) {
	if(currentState != state) {
		std::cout << currentState << " -> " << state << '\n';
		currentState = state;
		updateAnimation();
	}
}



void Creature::updateState() {
	std::cout << currentState << " -> ";
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
	std::cout << currentState << '\n';
	if(currentState != state) {
		updateAnimation();
	}
}



void Creature::updateAnimation() {
	if(animationTween) {
		animationTween->complete();
		animationTween->remove();
	}

	switch(currentState) {
	case State::Idle:{
		auto tween = Sprite::TweenAnim(animation, 0);
		tween.setInterval(0, 11);
		animationTween = sprite->addTween(tween, 600, -1);
		break;
	}
	case State::Run:{
		auto tween = Sprite::TweenAnim(animation, 2);
		tween.setInterval(0, 7);
		animationTween = sprite->addTween(tween, 600, -1);
		break;
	}
	case State::Attack:{
		auto tween = Sprite::TweenAnim(animation, 3);
		tween.setInterval(0, 10);
		animationTween = createTween(tween, 600, 1);
		sprite->addTween(TweenQueue::create(animationTween))->
			setDoneCallback([this](Event*) {
				updateState();
			});
		break;
	}
	case State::Decay:{
		auto tween = Sprite::TweenAnim(animation, 5);
		tween.setInterval(0, 13);
		animationTween = sprite->addTween(tween, 600, 1);
		break;
	}
	}
}
