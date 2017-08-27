#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "audio/include/SimpleAudioEngine.h"

using namespace cocos2d;
using namespace ui;
using namespace CocosDenshion;

static const char s_SendScore[] = "SendScoreButton.png";

class Game : public cocos2d::Scene, public ui::EditBoxDelegate
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    CREATE_FUNC(Game);
    
    // If this is going to be used in every scene, is there somewhere else it can be defined just once?
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    SimpleAudioEngine* audio = SimpleAudioEngine::getInstance();
    const int padding = 20;
    int answer = 0;
    int numberOfGuesses = 0;
    int guess = 0;
    void inputClicked();
    void makeGuess(cocos2d::Ref* sender);
    void passByReference(int *x);
    void wrongGuess();
    void notAllowedGuess();
private:
    void editBoxEditingDidBegin(EditBox* editBox);
    void editBoxTextChanged(EditBox* editBox, const std::string& text);
    void editBoxReturn(EditBox* editBox);
};

#endif // __GAME_SCENE_H__
