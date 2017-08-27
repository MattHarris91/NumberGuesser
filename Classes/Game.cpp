#include "Game.h"
#include "GameOver.h"

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
    
    answer = RandomHelper::random_int(1, 10);
    auto guessesLeft = Label::createWithTTF("Guesses Left: 3", "fonts/bitbox.ttf", 12);
    auto guessText = Label::createWithTTF("What number am I thinking of?", "fonts/bitbox.ttf", 16);
    // TODO - Change this from example and look into better positioning (relative to text?), also use nicer audio for winning / losing and maybe background music?
    std::string pNormalSprite = "sliderTrack.png";
    EditBox *_editName = EditBox::create(Size(100, 20), Scale9Sprite::create(pNormalSprite));
    auto submitGuessButton = MenuItemImage::create(s_SendScore, s_SendScore, CC_CALLBACK_1(Game::makeGuess, this) );
    auto menu = Menu::create(submitGuessButton, nullptr);
    auto wrongGuessText = Label::createWithTTF("Nope, I\'m not thinking of that number. Try again!", "fonts/bitbox.ttf", 16);
    auto notAllowedGuessText = Label::createWithTTF("Please enter a number between 1 and 10.", "fonts/bitbox.ttf", 16);
    
    guessesLeft->setPosition(Vec2(origin.x + visibleSize.width - (guessesLeft->getContentSize().width / 2) - padding,
                                  origin.y + visibleSize.height - (guessesLeft->getContentSize().height / 2) - padding));
    
    guessText->setWidth(visibleSize.width - (padding * 2));
    guessText->setPosition(Vec2(origin.x + visibleSize.width / 2,
                            origin.y + visibleSize.height - guessesLeft->getContentSize().height - guessText->getContentSize().height - padding));
    guessText->setAlignment(TextHAlignment::CENTER);
    
    _editName->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                origin.y + visibleSize.height - guessesLeft->getContentSize().height - guessText->getContentSize().height - (padding * 3)));
    _editName->setFontName("Paint Boy");
    _editName->setFontSize(18);
    _editName->setFontColor(Color3B::RED);
    _editName->setMaxLength(2);
    _editName->setInputMode(EditBox::InputMode::NUMERIC);
    _editName->setReturnType(EditBox::KeyboardReturnType::DONE);
    // Once text is in, this is no longer center...why?
    _editName->setTextHorizontalAlignment(TextHAlignment::CENTER);
    // TODO look into why this is done as a delegate
    _editName->setDelegate(this);
    
    menu->setNormalizedPosition(Vec2(0.5f, -0.5f));
    
    wrongGuessText->setWidth(visibleSize.width - (padding * 2));
    wrongGuessText->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                     origin.y + wrongGuessText->getContentSize().height + padding));
    wrongGuessText->setAlignment(TextHAlignment::CENTER);
    wrongGuessText->setOpacity(0);
    
    notAllowedGuessText->setWidth(visibleSize.width - (padding * 2));
    notAllowedGuessText->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                          origin.y + notAllowedGuessText->getContentSize().height + padding));
    notAllowedGuessText->setAlignment(TextHAlignment::CENTER);
    notAllowedGuessText->setOpacity(0);
    
    this->addChild(guessText);
    this->addChild(guessesLeft, 1, "guessesLeft");
    this->addChild(_editName);
    this->addChild(wrongGuessText, 1, "wrongGuessText");
    this->addChild(notAllowedGuessText, 1, "notAllowedGuessText");
    
    _editName->addChild(menu);
    
    return true;
}

void Game::makeGuess(Ref* sender)
{
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
    // TODO How has this worked? Is there a better way?
    auto guessesLeft = dynamic_cast<Label*>(Director::getInstance()->getRunningScene()->getChildByName("guessesLeft"));
    string guessesLeftFull = StringUtils::format("Guesses Left: %i", 3 - numberOfGuesses);
    
    audio->playEffect("audio/wrong.mp3");
    guessesLeft->setString(guessesLeftFull);
    wrongGuessText->runAction(fadeIn);
}

void Game::notAllowedGuess()
{
    FadeIn* fadeIn = FadeIn::create(0.5f);
    auto notAllowedGuess = this->getChildByName("notAllowedGuessText");
    
    audio->playEffect("audio/button.mp3");
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
};

/**
 * This method is called when the return button was pressed or the outside area of keyboard was touched.
 * @param editBox The edit box object that generated the event.
 */
void Game::editBoxReturn(EditBox* editBox) {};
