#include "MainActor.hpp"



MainActor::MainActor(Resources* resources):
	resources {resources} {
    button = new Sprite();
    button->setResAnim(resources->getResAnim("button"));
    Vector2 pos = getStage()->getSize() / 2 - button->getSize() / 2;
    button->setPosition(pos);
    EventCallback callback = CLOSURE(this, &MainActor::buttonClicked);
    button->addEventListener(TouchEvent::CLICK, callback);
    button->addEventListener(TouchEvent::CLICK, 
                            [](Event* e) {
                                oxygine::log::messageln("button clicked");
                            });
    addChild(button);
    text = new TextField();
    text->attachTo(button);
    text->setPosition(button->getSize() / 2);
    TextStyle style;
    style.font = resources->getResFont("main");
    style.color = Color::White;
    style.vAlign = TextStyle::VALIGN_MIDDLE;
    style.hAlign = TextStyle::HALIGN_CENTER;
    text->setStyle(style);
    text->setText("Click\nMe!");
}



void MainActor::buttonClicked(Event* event) {
    button->setColor(Color::White);
    button->addTween(Sprite::TweenColor(Color::Green), 500, 1, true);
    text->setScale(1.0f);
    text->addTween(Actor::TweenScale(1.1f), 500, 1, true);
    text->setText("Clicked!");
    runSprite();
}



void MainActor::runSprite() {
    spSprite sprite = new Sprite();
    addChild(sprite);
    int duration = 600;//ms
    int loops = -1;//infinity loops
    ResAnim* animation = resources->getResAnim("anim");
    sprite->addTween(Sprite::TweenAnim(animation), duration, loops);
    Vector2 destPos = getStage()->getSize() - sprite->getSize();
    Vector2 srcPos = Vector2(0, destPos.y);
    sprite->setPosition(srcPos);
    spTweenQueue tweenQueue = new TweenQueue();
    tweenQueue->setDelay(1500);
    tweenQueue->add(Sprite::TweenPosition(destPos), 2500, 1);
    tweenQueue->add(Sprite::TweenAlpha(0), 500, 1);
    sprite->addTween(tweenQueue);
    tweenQueue->detachWhenDone();
}
