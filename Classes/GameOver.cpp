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
    
    string gameOverText = didWin ? "You win!" : "You lose.";

    auto message = Label::createWithTTF(gameOverText, "fonts/Marker Felt.ttf", 16);
    message->setWidth(visibleSize.width - (padding * 2));
    message->setPosition(Vec2(origin.x + visibleSize.width / 2,
                            origin.y + visibleSize.height - message->getContentSize().height));
    message->setAlignment(TextHAlignment::CENTER);
    
    this->addChild(message);
    
    auto tryAgain = MenuItemLabel::create(Label::createWithTTF("Play Again?", "fonts/Marker Felt.ttf", 16), CC_CALLBACK_1(GameOver::restartGame, this));
    auto menu = Menu::create(tryAgain, nullptr);
    menu->setPosition(Vec2(origin.x + visibleSize.width / 2,
                               origin.y + visibleSize.height - message->getContentSize().height - (padding * 2)));

    this->addChild(menu);
    
    return true;
}

void GameOver::restartGame(Ref* sender)
{
    auto scene = Game::createScene();
    Director::getInstance()->replaceScene(scene);
}
