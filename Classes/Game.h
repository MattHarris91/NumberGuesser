#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
//#include "ui/CocosGUI.h"

using namespace cocos2d;

class Game : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    CREATE_FUNC(Game);
    
    // If this is going to be used in every scene, is there somewhere else it can be defined just once?
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    const int padding = 20;
    //CC_SYNTHESIZE(ui::EditBoxDelegate*, _delegate, Delegate);
};

#endif // __GAME_SCENE_H__
