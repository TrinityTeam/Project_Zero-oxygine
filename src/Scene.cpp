#include "Scene.hpp"
#include <Input.h>
#include <SDL.h>
#include <SDL_keyboard.h>
using oxygine::getStage;
using oxygine::TouchEvent;
using oxygine::KeyEvent;
using oxygine::EventCallback;
using oxygine::Input;



Scene::Scene(Resources* resources):
	resources {resources} {
    character = new Creature(resources);
    addChild(character);
    character->setPosition(getStage()->getSize() / 2);

    EventCallback touchCallback = CLOSURE(this, &Scene::buttonClicked);
    getStage()->addEventListener(TouchEvent::CLICK, touchCallback);
    EventCallback keyboardCallback = CLOSURE(this, &Scene::keyReleased);
    getStage()->addEventListener(KeyEvent::KEY_UP, keyboardCallback);
}



void Scene::buttonClicked(Event* e) {
    TouchEvent* event = static_cast<TouchEvent*>(e);
    character->moveTo(event->localPosition);
}



void Scene::keyReleased(Event* e) {
    auto event = static_cast<KeyEvent*>(e);

    switch (event->data->keysym.sym) {
    case SDLK_RETURN:           
            
        break;
    
    case SDLK_SPACE:            
        character->attack();
        break;
    
    default:
        ;
    }
}
