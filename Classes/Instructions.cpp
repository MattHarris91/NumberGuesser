#include "Instructions.h"
#include "Game.h"

using namespace std;
USING_NS_CC;

Scene* Title::createScene()
{
    return Title::create();
}

// on "init" you need to initialize your instance
bool Title::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    auto title = Label::createWithTTF("NUMBER\nGUESSER", "fonts/bitbox.ttf", 32);
    auto play = Label::createWithTTF("TAP SCREEN\nTO PLAY", "fonts/bitbox.ttf", 24);
    auto listener1 = EventListenerTouchOneByOne::create();
    
    title->setWidth(visibleSize.width - (padding * 2));
    title->setPosition(Vec2(origin.x + visibleSize.width / 2,
                            origin.y + visibleSize.height - title->getContentSize().height));
    title->setAlignment(TextHAlignment::CENTER);
    
    play->setWidth(visibleSize.width - (padding * 2));
    play->setPosition(Vec2(origin.x + visibleSize.width / 2,
                            origin.y + visibleSize.height / 2 - play->getContentSize().height * 2));
    play->setAlignment(TextHAlignment::CENTER);
    
    listener1->onTouchBegan = [](Touch* touch, Event* event){
        auto scene = Instructions::createScene();
        Director::getInstance()->replaceScene(scene);
        return false;
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
    
    this->addChild(title);
    this->addChild(play);
    
    return true;
}

Scene* Instructions::createScene()
{
    return Instructions::create();
}

bool Instructions::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    
    // TODO - Is there a nicer way to create multiple labels and add them?
    string instructionsText = "This is a number guessing game where I will \"think\" of a number between 1 and 10 and you will have 3 tries to guess the right number.\n\nSound easy enough? We will see!\n\nTap to start";
    auto title = Label::createWithTTF("Instructions", "fonts/bitbox.ttf", 24);
    auto instructions = Label::createWithTTF(instructionsText, "fonts/bitbox.ttf", 16);
    auto listener1 = EventListenerTouchOneByOne::create();
    
    title->setWidth(visibleSize.width - (padding * 2));
    title->setPosition(Vec2(origin.x + visibleSize.width / 2,
                            origin.y + visibleSize.height - title->getContentSize().height));
    title->setAlignment(TextHAlignment::CENTER);
    
    instructions->setWidth(visibleSize.width - (padding * 2));
    instructions->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                   origin.y + visibleSize.height - (title->getContentSize().height * 6)));
    instructions->setAlignment(TextHAlignment::CENTER);
    
    // TODO - research lambda
    listener1->onTouchBegan = [](Touch* touch, Event* event){
        auto scene = Game::createScene();
        Director::getInstance()->replaceScene(scene);
        return false;
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
    
    this->addChild(title, 1);
    this->addChild(instructions, 1);
    
    return true;
}
