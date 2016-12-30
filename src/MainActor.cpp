#include "MainActor.hpp"
using oxygine::getStage;
using oxygine::TouchEvent;
using oxygine::EventCallback;



MainActor::MainActor(Resources* resources):
	resources {resources} {
    character = new Creature(resources);
    addChild(character);
    character->setPosition(getStage()->getSize() / 2);

    EventCallback callback = CLOSURE(this, &MainActor::buttonClicked);
    getStage()->addEventListener(TouchEvent::CLICK, callback);
}



void MainActor::buttonClicked(Event* e) {
    TouchEvent* event = static_cast<TouchEvent*>(e);
    character->moveTo(event->localPosition);
}
