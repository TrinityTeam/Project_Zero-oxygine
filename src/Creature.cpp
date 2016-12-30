#include "Creature.hpp"
using oxygine::TextStyle;
using oxygine::Color;
using oxygine::ResAnim;
using oxygine::TextField;



Creature::Creature(Resources* resources):
	resources {resources} {
	setAnchor({0.5, 0.5});
	sprite = new Sprite();
	sprite->setAnchor({0.5, 0.5});
    addChild(sprite);
    ResAnim* animation = resources->getResAnim("anim");
    int duration = 600;//ms
    int loops = -1;//infinity loops
    sprite->addTween(Sprite::TweenAnim(animation), duration, loops);

    nameBar = new TextField();
    nameBar->attachTo(this);
    nameBar->setY(-sprite->getSize().y/2);
    TextStyle style;
    style.font = resources->getResFont("main");
    style.color = Color::White;
    style.vAlign = TextStyle::VALIGN_MIDDLE;
    style.hAlign = TextStyle::HALIGN_CENTER;
    nameBar->setStyle(style);
    nameBar->setText("Anonymous");
}



void Creature::moveTo(Vector2 destination) {
	int direction = (destination.x > getPosition().x) ? 1 : -1; 
    sprite->setScaleX(direction);

	addTween(Sprite::TweenPosition(destination), 2500, 1);
}