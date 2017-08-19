#include "Game.h"
#include "ui/CocosGUI.h"

using namespace std;
USING_NS_CC;

Scene* Game::createScene()
{
    return Game::create();
}

// on "init" you need to initialize your instance
bool Game::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    auto label = Label::createWithTTF("What number am I thinking of?", "fonts/Marker Felt.ttf", 16);
    
    label->setWidth(visibleSize.width - (padding * 2));
    label->setPosition(Vec2(origin.x + visibleSize.width / 2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    label->setAlignment(TextHAlignment::CENTER);
    
    this->addChild(label, 1);
    
    // TODO - Change this from example
    std::string pNormalSprite = "green_edit.png";
    ui::EditBox *_editName = ui::EditBox::create(Size(100, 100), ui::Scale9Sprite::create(pNormalSprite));
    _editName->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                  origin.y + visibleSize.height - (label->getContentSize().height * 2)));
    _editName->setFontName("Paint Boy");
    _editName->setFontSize(25);
    _editName->setFontColor(Color3B::RED);
    _editName->setMaxLength(2);
    _editName->setInputMode(ui::EditBox::InputMode::NUMERIC);
    _editName->setReturnType(ui::EditBox::KeyboardReturnType::DONE);

    // TODO - Research delegates and do I need one here?
    //_editName->setDelegate(_delegate);
    
    this->addChild(_editName);
    
    /* *** TODO ***
     * Button to submit guess
     * Keep track of number of guesses
     * Handle wrong guess
     * Handle win
     * Handle lose
     */

    
    return true;
}
