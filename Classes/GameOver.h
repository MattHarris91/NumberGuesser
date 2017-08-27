#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#include "cocos2d.h"
#include "audio/include/SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

class GameOver : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene(bool didWin);
    
    virtual bool init();
    CREATE_FUNC(GameOver);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    SimpleAudioEngine* audio = SimpleAudioEngine::getInstance();
    const int padding = 20;
    void restartGame(Ref* sender);
};

#endif // __GAMEOVER_SCENE_H__
