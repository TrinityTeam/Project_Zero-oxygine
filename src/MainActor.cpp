#include "MainActor.hpp"
using oxygine::Sprite;
using oxygine::getStage;
using oxygine::TouchEvent;
using oxygine::EventCallback;
using oxygine::TextStyle;
using oxygine::Color;
using oxygine::ResAnim;



MainActor::MainActor(Resources* resources):
	resources {resources} {
    character = new Sprite();
    character->setAnchor({0.5, 0.5});
    addChild(character);
    ResAnim* animation = resources->getResAnim("anim");
    int duration = 600;//ms
    int loops = -1;//infinity loops
    character->addTween(Sprite::TweenAnim(animation), duration, loops);
    character->setPosition(getStage()->getSize() / 2);

    
    EventCallback callback = CLOSURE(this, &MainActor::buttonClicked);
    getStage()->addEventListener(TouchEvent::CLICK, callback);

    text = new TextField();
    text->attachTo(character);
    text->setPosition(character->getSize() / 2);
    TextStyle style;
    style.font = resources->getResFont("main");
    style.color = Color::White;
    style.vAlign = TextStyle::VALIGN_MIDDLE;
    style.hAlign = TextStyle::HALIGN_CENTER;
    text->setStyle(style);
    text->setText("LELOUCH IS ALIVE");
}



void MainActor::buttonClicked(Event* e) {
    TouchEvent* event = static_cast<TouchEvent*>(e);

    character->setColor(Color::White);
    character->addTween(Sprite::TweenColor(Color::Green), 500, 1, true);
    int direction = (event->localPosition.x > character->getPosition().x) ? 1 : -1; 
    character->setScaleX(direction);
    text->setScaleX(direction);
    text->addTween(Actor::TweenScale(Vector2 {direction*1.1f, 1.1f}), 500, 1, true);
    text->setText("Still alive");
    runSprite(event->localPosition);
}



void MainActor::runSprite(Vector2 destination) {
    character->addTween(Sprite::TweenPosition(destination), 2500, 1);
}
