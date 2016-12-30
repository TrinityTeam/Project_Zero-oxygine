#pragma once
#include "oxygine-framework.h"
using oxygine::Actor;
using oxygine::Vector2;
using oxygine::Event;
using oxygine::TextField;
using oxygine::TweenQueue;
using oxygine::spSprite;
using oxygine::spTextField;
using oxygine::Resources;



class MainActor: public Actor {
public:
    MainActor(Resources* resources);

private:
    void buttonClicked(Event* event);
    void runSprite(Vector2 destination);

	Resources* resources {};
    spTextField text {};
    spSprite character {};
};



using spMainActor = oxygine::intrusive_ptr<MainActor>;
