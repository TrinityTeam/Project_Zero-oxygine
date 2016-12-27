#pragma once
#include "oxygine-framework.h"
using oxygine::Sprite;
using oxygine::Actor;
using oxygine::Vector2;
using oxygine::Event;
using oxygine::getStage;
using oxygine::TouchEvent;
using oxygine::EventCallback;
using oxygine::TextStyle;
using oxygine::TextField;
using oxygine::TweenQueue;
using oxygine::spSprite;
using oxygine::spTweenQueue;
using oxygine::spTextField;
using oxygine::Color;
using oxygine::Resources;
using oxygine::ResAnim;



class MainActor: public Actor {
public:
    MainActor(Resources* resources);

private:
    void buttonClicked(Event* event);
    void runSprite();

	Resources* resources {};
    spTextField text {};
    spSprite button {};
};



using spMainActor = oxygine::intrusive_ptr<MainActor>;
