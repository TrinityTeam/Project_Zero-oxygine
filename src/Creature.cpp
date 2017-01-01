#include "Creature.hpp"
using oxygine::TextStyle;
using oxygine::Color;
using oxygine::TextField;
using oxygine::Event;



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

    auto tweenPosition = Sprite::TweenPosition(destination);
    setAnimation(Animation::Run);
	removeTween(positionTween); // TODO: Replace removing old tween with redirecting destination
	positionTween = addTween(tweenPosition, 2500, 1);
	positionTween->setDoneCallback(
		[this](Event*) { setAnimation(Animation::Idle); });
}



void Creature::setAnimation(Animation animation_id) {
	removeTween(animationTween);

	switch(animation_id) {
	case Animation::Idle:{
    	auto tween = Sprite::TweenAnim(animation, 0);
    	tween.setInterval(0, 11);
    	animationTween = sprite->addTween(tween, 600, -1);
		break;
	}
	case Animation::Run:{
	    	auto tween = Sprite::TweenAnim(animation, 2);
	    	tween.setInterval(0, 7);
	    	animationTween = sprite->addTween(tween, 600, -1);
			break;
		}
	case Animation::Attack:{
	    	auto tween = Sprite::TweenAnim(animation, 3);
	    	tween.setInterval(0, 10);
	    	animationTween = sprite->addTween(tween, 600, 1);
			break;
		}
	case Animation::Death:{
	    	auto tween = Sprite::TweenAnim(animation, 5);
	    	tween.setInterval(0, 13);
	    	animationTween = sprite->addTween(tween, 600, 1);
			break;
		}
	}
}
