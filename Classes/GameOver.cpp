#include "GameOver.h"
#include "Game.h"

using namespace std;
USING_NS_CC;

bool didWin;

Scene* GameOver::createScene(bool b)
{
    didWin = b;
    return GameOver::create();
}

bool GameOver::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    
    const char* audioToUse = didWin ? "audio/right.mp3" : "audio/wrong.mp3";
    string gameOverText = didWin ? "You win!" : "You lose.";
    auto message = Label::createWithTTF(gameOverText, "fonts/bitbox.ttf", 16);
    auto tryAgain = MenuItemLabel::create(Label::createWithTTF("Play Again?", "fonts/bitbox.ttf", 16), CC_CALLBACK_1(GameOver::restartGame, this));
    auto menu = Menu::create(tryAgain, nullptr);
    
    message->setWidth(visibleSize.width - (padding * 2));
    message->setPosition(Vec2(origin.x + visibleSize.width / 2,
                            origin.y + visibleSize.height - message->getContentSize().height));
    message->setAlignment(TextHAlignment::CENTER);
    
    menu->setPosition(Vec2(origin.x + visibleSize.width / 2,
                           origin.y + visibleSize.height - message->getContentSize().height - (padding * 2)));
    
    audio->playEffect(audioToUse);
    
    this->addChild(message);
    this->addChild(menu);
    
    return true;
}

void GameOver::restartGame(Ref* sender)
{
    auto scene = Game::createScene();
    Director::getInstance()->replaceScene(scene);
}
