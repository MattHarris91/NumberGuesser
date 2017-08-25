#include "Instructions.h"
#include "Game.h"

using namespace std;
USING_NS_CC;

Scene* Instructions::createScene()
{
    return Instructions::create();
}

// on "init" you need to initialize your instance
bool Instructions::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    // TODO - Is there a nicer way to create multiple labels and add them?
    string instructionsText = "This is a number guessing game where I will \"think\" of a number between 1 and 10 and you will have 3 tries to guess the right number.\n\nSound easy enough? We will see!\n\nTap to start";
    
    auto title = Label::createWithTTF("Instructions", "fonts/Marker Felt.ttf", 24);
    auto instructions = Label::createWithTTF(instructionsText, "fonts/Marker Felt.ttf", 16);
    
    title->setWidth(visibleSize.width - (padding * 2));
    title->setPosition(Vec2(origin.x + visibleSize.width / 2,
                            origin.y + visibleSize.height - title->getContentSize().height));
    title->setAlignment(TextHAlignment::CENTER);
    
    this->addChild(title, 1);
    
    instructions->setWidth(visibleSize.width - (padding * 2));
    instructions->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                   origin.y + visibleSize.height - (title->getContentSize().height * 6)));
    instructions->setAlignment(TextHAlignment::CENTER);
    this->addChild(instructions, 1);
    
    auto listener1 = EventListenerTouchOneByOne::create();
    
    // TODO - research lambda
    listener1->onTouchBegan = [](Touch* touch, Event* event){
        auto scene = Game::createScene();
        Director::getInstance()->replaceScene(scene);
        return false;
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
    
    
    return true;
}
