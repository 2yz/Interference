#include "HUDLayer.h"
#include <strstream>
#include "HelloWorldScene.h"
#include "Message.h"
#include "ConfigUtil.h"

USING_NS_CC;

HUDLayer::HUDLayer() : score(0), scoreLabel(nullptr), pauseButtonItem(nullptr), launchButtonItem(nullptr), HPIndicator(nullptr), pauseButton(nullptr), launchButton(nullptr)
{
}

bool HUDLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(HUDLayer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	scoreLabel = Label::createWithTTF("0", MARKER_FELT_FONT, 60);
	scoreLabel->setAnchorPoint(Vec2(1.0f, 1.0f));
	scoreLabel->setPosition(config::visible_origin.x + config::visible_size.width - 50, config::visible_origin.y + config::visible_size.height - 50);
	this->addChild(scoreLabel);

	auto test = Label::createWithBMFont(NUMBER_BMFONT, "01:23");
	test->setScale(0.2f);
	test->setBlendFunc(BlendFunc::ADDITIVE);
	test->setPosition(200.0f, 200.0f);
	addChild(test);

	// pauseButtonItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("pauseButton.png"), Sprite::createWithSpriteFrameName("pauseButton.png"), CC_CALLBACK_1(HUDLayer::menuPauseCallback, this));
	// pauseButton = Menu::create(pauseButtonItem, nullptr);
	// //pauseButton->setAnchorPoint(Point(0.0f, 1.0f));
	// //pauseButton->setPosition(75, visibleOrigin.y + visibleSize.height - 75);
	// pauseButton->setPosition(500.0f, 500.0f);
	// this->addChild(pauseButton);

	setEventListener();

	return true;
}

void HUDLayer::setEventListener()
{
	auto listener = EventListenerCustom::create("TimeEvent", [=](EventCustom* event)
	{
		int* buf = static_cast<int*>(event->getUserData());
		log("TimeEvent %d", *buf);
	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	auto score_listener = EventListenerCustom::create(kScoreEvent, [=](EventCustom* event)
	{
		int* buf = static_cast<int*>(event->getUserData());
		score += *buf;
		log("# Score #\n%d", score);
	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(score_listener, this);
}

void HUDLayer::addScoreBy(int addScore)
{
	score += addScore;
	updateScore();
}

void HUDLayer::updateHPIndicator()
{
	// int HP = static_cast<PlayerUserData*>(static_cast<BattleScene*>(this->getParent())->getCameraLayer()->getPlayerLayer()->getMyPlane()->getUserData())->getHP();
	// int initHP = static_cast<BattleScene*>(this->getParent())->getCameraLayer()->getPlayerLayer()->getInitHP();
	// float HPOld = HPIndicator->getPercentage();
	// float HPPercentage = static_cast<float>(HP) / static_cast<float>(initHP);
	// ProgressFromTo* animation = ProgressFromTo::create(0.2f, HPOld, HPPercentage * 100);
	// HPIndicator->runAction(animation);
}

void HUDLayer::setLaunchButtonEnable()
{
	launchButtonItem->setEnabled(true);
	launchButton->setEnabled(true);
}

int HUDLayer::getScore()
{
	return score;
}

void HUDLayer::updateScore()
{
	std::string strScore;
	std::strstream ss;
	ss << this->score;
	ss >> strScore;
	scoreLabel->setString(strScore.c_str());
	// TODO GiftLayer
	// if (this->score % 1000 == 0){
	// 	static_cast<BattleScene*>(this->getParent())->getUFOLayer()->addGiftSprite();
	// }
}

void HUDLayer::menuPauseCallback(cocos2d::Ref* pSender)
{
	//如果游戏已在暂停中
	if (Director::getInstance()->isPaused())
	{
		Director::getInstance()->resume();
		Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(1);
		pauseButtonItem->setNormalImage(Sprite::createWithSpriteFrameName("pauseButton.png"));
		pauseButtonItem->setSelectedImage(Sprite::createWithSpriteFrameName("startButton.png"));
	}
	else
	{
		//如果游戏正在进行
		Director::getInstance()->pause();
		Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(0);
		pauseButtonItem->setNormalImage(Sprite::createWithSpriteFrameName("startButton.png"));
		pauseButtonItem->setSelectedImage(Sprite::createWithSpriteFrameName("pauseButton.png"));
	}
}

void HUDLayer::menuLaunchCallback(cocos2d::Ref* pSender)
{
	launchButtonItem->setEnabled(false);
	launchButton->setEnabled(false);
}

void HUDLayer::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event)
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

void HUDLayer::update(float deltaTime)
{

}