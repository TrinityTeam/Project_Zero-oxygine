#include "MainActor.hpp"



MainActor::MainActor(Resources* resources):
	resources {resources} {
    character = new Sprite();
    addChild(character);
    ResAnim* animation = resources->getResAnim("anim");
    int duration = 600;//ms
    int loops = -1;//infinity loops
    character->addTween(Sprite::TweenAnim(animation), duration, loops);
    character->setPosition(getStage()->getSize() / 2 - character->getSize() / 2);
    
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
    text->setScale(1.0f);
    text->addTween(Actor::TweenScale(1.1f), 500, 1, true);
    text->setText("Still alive");
    runSprite(event->localPosition);
}



void MainActor::runSprite(Vector2 destination) {
    character->addTween(Sprite::TweenPosition(destination - character->getSize()/2), 2500, 1);
}
