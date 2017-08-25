#include "Game.h"
#include "GameOver.h"
#include "ui/CocosGUI.h"


using namespace std;
using namespace ui;
USING_NS_CC;

Scene* Game::createScene()
{
    return Game::create();
}

bool Game::init()
{
    
    if ( !Scene::init() )
    {
        return false;
    }
    
    answer = RandomHelper::random_int(1, 10);;
    log("%i", answer);

    auto guessText = Label::createWithTTF("What number am I thinking of?", "fonts/Marker Felt.ttf", 16);
    
    guessText->setWidth(visibleSize.width - (padding * 2));
    guessText->setPosition(Vec2(origin.x + visibleSize.width / 2,
                            origin.y + visibleSize.height - guessText->getContentSize().height));
    guessText->setAlignment(TextHAlignment::CENTER);
    
    this->addChild(guessText);
    
    // TODO - Change this from example and look into better positioning (relative to text?)
    std::string pNormalSprite = "sliderTrack.png";
    EditBox *_editName = EditBox::create(Size(100, 20), Scale9Sprite::create(pNormalSprite));
    _editName->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                  origin.y + visibleSize.height - (guessText->getContentSize().height * 2)));
    _editName->setFontName("Paint Boy");
    _editName->setFontSize(18);
    _editName->setFontColor(Color3B::RED);
    _editName->setMaxLength(2);
    _editName->setInputMode(EditBox::InputMode::NUMERIC);
    _editName->setReturnType(EditBox::KeyboardReturnType::DONE);
    _editName->setTextHorizontalAlignment(TextHAlignment::CENTER);
    // TODO look into why this is done as a delegate
    _editName->setDelegate(this);
    
    this->addChild(_editName);
    
    auto submitGuessButton = MenuItemImage::create(s_SendScore, s_SendScore, CC_CALLBACK_1(Game::makeGuess, this) );
    //submitGuessButton->setAnchorPoint(Point(0, 0));
    
    auto menu = Menu::create(submitGuessButton, nullptr);
    menu->setNormalizedPosition(Vec2(0.5f, -0.5f));
    //menu->setPosition(Vec2(2.5, 2.5));
    
    _editName->addChild(menu);
    
    auto wrongGuessText = Label::createWithTTF("Nope, I\'m not thinking of that number. Try again!", "fonts/Marker Felt.ttf", 16);
    
    wrongGuessText->setWidth(visibleSize.width - (padding * 2));
    wrongGuessText->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                     origin.y + wrongGuessText->getContentSize().height + padding));
    wrongGuessText->setAlignment(TextHAlignment::CENTER);
    wrongGuessText->setOpacity(0);
    
    this->addChild(wrongGuessText, 1, "wrongGuessText");

    auto notAllowedGuessText = Label::createWithTTF("Please enter a number between 1 and 10.", "fonts/Marker Felt.ttf", 16);
    
    notAllowedGuessText->setWidth(visibleSize.width - (padding * 2));
    notAllowedGuessText->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                     origin.y + notAllowedGuessText->getContentSize().height + padding));
    notAllowedGuessText->setAlignment(TextHAlignment::CENTER);
    notAllowedGuessText->setOpacity(0);
    
    this->addChild(notAllowedGuessText, 1, "notAllowedGuessText");

    
    /* *** TODO ***
     * Y Button to submit guess
     * Y Keep track of number of guesses
     * Y Handle wrong guess
     * Y Handle win
     * Y Handle lose
     * N Number of guesses left displayed to player
     */
    
    return true;
}

void Game::makeGuess(Ref* sender)
{
    log("answer: %i", answer);
    log("number of guesses: %i", numberOfGuesses);
    
    if (guess < 1 || guess > 10)
    {
        Game::notAllowedGuess();
    } else
    {
        numberOfGuesses++;
        if (guess == answer)
        {
            auto scene = GameOver::createScene(true);
            Director::getInstance()->replaceScene(scene);
        } else if (numberOfGuesses == 3)
        {
            auto scene = GameOver::createScene(false);
            Director::getInstance()->replaceScene(scene);
        } else
        {
            Game::wrongGuess();
        }
    }
    
}

void Game::wrongGuess()
{
    FadeIn* fadeIn = FadeIn::create(0.5f);
    auto wrongGuessText = this->getChildByName("wrongGuessText");
    wrongGuessText->runAction(fadeIn);
}

void Game::notAllowedGuess()
{
    FadeIn* fadeIn = FadeIn::create(0.5f);
    auto notAllowedGuess = this->getChildByName("notAllowedGuessText");
    notAllowedGuess->runAction(fadeIn);
}

/**
 * This method is called when an edit box gains focus after keyboard is shown.
 * @param editBox The edit box object that generated the event.
 */
void Game::editBoxEditingDidBegin(EditBox* editBox)
{
    FadeOut* fadeOut1 = FadeOut::create(0.5f);
    FadeOut* fadeOut2 = FadeOut::create(0.5f);
    auto scene = Director::getInstance()->getRunningScene();
    
    auto wrongGuessText = scene->getChildByName("wrongGuessText");
    auto notAllowedGuessText = scene->getChildByName("notAllowedGuessText");
    notAllowedGuessText->runAction(fadeOut1);
    wrongGuessText->runAction(fadeOut2);
    
};

/**
 * This method is called when the edit box text was changed.
 * @param editBox The edit box object that generated the event.
 * @param text The new text.
 */
void Game::editBoxTextChanged(EditBox* editBox, const std::string& text)
{
    guess = atoi(text.c_str());
    log("guess: %i", guess);
};

/**
 * This method is called when the return button was pressed or the outside area of keyboard was touched.
 * @param editBox The edit box object that generated the event.
 */
void Game::editBoxReturn(EditBox* editBox) {};
