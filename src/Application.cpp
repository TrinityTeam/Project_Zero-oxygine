#include "Application.hpp"
#include "core/oxygine.h"
#include "Stage.h"
#include "Scene.hpp"
namespace core = oxygine::core;
using oxygine::getStage;
using oxygine::Rect;
using oxygine::ObjectBase;
using oxygine::Point;
using oxygine::Resources;
using oxygine::Color;
using oxygine::Stage;



void Application::run() {
    ObjectBase::__startTracingLeaks();

    core::init_desc desc;
    desc.title = "Project Zero";
    desc.w = 960;
    desc.h = 640;
    core::init(&desc);

    Stage::instance = new Stage(true);
    Point size = core::getDisplaySize();
    getStage()->setSize(size);

    Resources gameResources;
    gameResources.loadXML("res.xml");

    spScene actor = new Scene(&gameResources);
    getStage()->addChild(actor);

    while (true) {
        bool terminationRequested = loop();
        if (terminationRequested) {
            break;
        }
    }

    ObjectBase::dumpCreatedObjects();
    gameResources.free();
    core::release();
    ObjectBase::dumpCreatedObjects();
    ObjectBase::__stopTracingLeaks();
}



bool Application::loop() {
    bool terminationRequested = core::update();

    getStage()->update();

    if (core::beginRendering()) {
        Color clearColor(32, 32, 32, 255);
        Rect viewport(Point(0, 0), core::getDisplaySize());
        getStage()->render(clearColor, viewport);

        core::swapDisplayBuffers();
    }

    return terminationRequested;
}
