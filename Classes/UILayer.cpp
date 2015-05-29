#include "UILayer.h"
#include <strstream>
#include "HelloWorldScene.h"
#include "GameScene.h"
#include "PlayerUserData.h"

USING_NS_CC;

UILayer::UILayer() : score(0), scoreLabel(nullptr), pauseButtonItem(nullptr), launchButtonItem(nullptr), HPIndicator(nullptr), pauseButton(nullptr), launchButton(nullptr)
{
}

bool UILayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(UILayer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 visibleOrigin = Director::getInstance()->getVisibleOrigin();

	scoreLabel = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 60);
	scoreLabel->setAnchorPoint(Vec2(1.0f, 1.0f));
	scoreLabel->setPosition(visibleOrigin.x + visibleSize.width - 50, visibleOrigin.y + visibleSize.height - 50);
	this->addChild(scoreLabel);

	pauseButtonItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("pauseButton.png"), Sprite::createWithSpriteFrameName("pauseButton.png"), CC_CALLBACK_1(UILayer::menuPauseCallback, this));
	pauseButton = Menu::create(pauseButtonItem, nullptr);
	pauseButton->setAnchorPoint(Point(0.0f, 1.0f));
	pauseButton->setPosition(75, visibleOrigin.y + visibleSize.height - 75);
	this->addChild(pauseButton);

	Sprite* HPBottomSprite = Sprite::createWithSpriteFrameName("HPBottom.png");
	HPBottomSprite->setPosition(100, 100);
	this->addChild(HPBottomSprite);

	Sprite* HP = Sprite::createWithSpriteFrameName("HP.png");
	HPIndicator = ProgressTimer::create(HP);
	HPIndicator->setType(ProgressTimer::Type::RADIAL);
	HPIndicator->setPercentage(100);
	HPIndicator->setPosition(100, 100);
	this->addChild(HPIndicator, 0, 0);

	launchButtonItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("launchButton.png"), Sprite::createWithSpriteFrameName("launchButton.png"), Sprite::createWithSpriteFrameName("launchButtonUnable.png"), CC_CALLBACK_1(UILayer::menuLaunchCallback, this));
	launchButton = Menu::create(launchButtonItem, nullptr);
	launchButton->setPosition(100, 100);

	launchButtonItem->setEnabled(false);
	launchButton->setEnabled(false);

	this->addChild(launchButton);

	return true;
}

void UILayer::addScoreBy(int addScore)
{
	score += addScore;
	updateScore();
}

void UILayer::updateHPIndicator()
{
	int HP = static_cast<PlayerUserData*>(static_cast<GameScene*>(this->getParent())->getCameraLayer()->getPlayerLayer()->getMyPlane()->getUserData())->getHP();
	int initHP = static_cast<GameScene*>(this->getParent())->getCameraLayer()->getPlayerLayer()->getInitHP();
	float HPOld = HPIndicator->getPercentage();
	float HPPercentage = static_cast<float>(HP) / static_cast<float>(initHP);
	ProgressFromTo* animation = ProgressFromTo::create(0.2f, HPOld, HPPercentage * 100);
	HPIndicator->runAction(animation);
}

void UILayer::setLaunchButtonEnable()
{
	launchButtonItem->setEnabled(true);
	launchButton->setEnabled(true);
}

int UILayer::getScore()
{
	return score;
}

void UILayer::updateScore()
{
	std::string strScore;
	std::strstream ss;
	ss << this->score;
	ss >> strScore;
	scoreLabel->setString(strScore.c_str());
	// TODO GiftLayer
	// if (this->score % 1000 == 0){
	// 	static_cast<GameScene*>(this->getParent())->getUFOLayer()->addGiftSprite();
	// }
}

void UILayer::menuPauseCallback(cocos2d::Ref* pSender)
{
	//如果游戏已在暂停中
	if (Director::getInstance()->isPaused())
	{
		Director::getInstance()->resume();
		pauseButtonItem->setNormalImage(Sprite::createWithSpriteFrameName("pauseButton.png"));
		pauseButtonItem->setSelectedImage(Sprite::createWithSpriteFrameName("startButton.png"));
	}
	else
	{
		//如果游戏正在进行
		Director::getInstance()->pause();
		pauseButtonItem->setNormalImage(Sprite::createWithSpriteFrameName("startButton.png"));
		pauseButtonItem->setSelectedImage(Sprite::createWithSpriteFrameName("pauseButton.png"));
	}
}

void UILayer::menuLaunchCallback(cocos2d::Ref* pSender)
{
	launchButtonItem->setEnabled(false);
	launchButton->setEnabled(false);
}

void UILayer::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
{
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_BACK:
		// Director::getInstance()->end();
		Scene* helloWorld;
		helloWorld = TransitionFade::create(2.0f, HelloWorld::createScene());
		Director::getInstance()->replaceScene(helloWorld);
		break;
	default:
		break;
	}
}