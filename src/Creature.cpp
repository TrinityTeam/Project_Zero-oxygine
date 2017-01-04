#include "Creature.hpp"
using oxygine::TextStyle;
using oxygine::Color;
using oxygine::TextField;
using oxygine::Event;
using oxygine::TweenT;



Creature::Creature(Resources* resources):
	resources {resources} {
	setAnchor({0.5, 0.5});
	sprite = new Sprite();
	sprite->setAnchor({0.5, 0.5});
    addChild(sprite);
    animation = resources->getResAnim("General Zirix Starstrider");
    
    setAnimation(Animation::Idle);

    nameBar = new TextField();
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

	removeTween(positionTween);
	positionTween = addTween(Sprite::TweenPosition(destination), 2500, 1);
	positionTween->setDoneCallback(
		[this](Event*) { setAnimation(Animation::Idle); });
	setAnimation(Animation::Run);
}



void Creature::attack() {
	setAnimation(Animation::Strike);
}



void Creature::setAnimation(Animation animation_id) {
	removeTween(animationTween);

	switch(animation_id) {
	case Animation::Idle:{
		auto tween = Sprite::TweenAnim(animation, 0);
		tween.setInterval(0, 11);
		animationTween = sprite->addTween(tween, 600, -1);
		currentState = animation_id;
		break;
	}
	case Animation::Run:{
		auto tween = Sprite::TweenAnim(animation, 2);
		tween.setInterval(0, 7);
		animationTween = sprite->addTween(tween, 600, -1);
		currentState = animation_id;
		break;
		}
	case Animation::Strike:{
		if(currentState == Animation::Strike and 
		   animationTween->isStarted() and not animationTween->isDone()) {
			break;
		}
		auto tween = Sprite::TweenAnim(animation, 3);
		tween.setInterval(0, 10);
		animationTween = sprite->addTween(tween, 600, 1);
		currentState = animation_id;
		animationTween->setDoneCallback([this](Event*) {
			if(positionTween->isDone()) {
				setAnimation(Animation::Idle);
			} else {
				setAnimation(Animation::Run);
			}
		});
		break;
		}
	case Animation::Death:{
		auto tween = Sprite::TweenAnim(animation, 5);
		tween.setInterval(0, 13);
		animationTween = sprite->addTween(tween, 600, 1);
		currentState = animation_id;
		break;
		}
	}
}
