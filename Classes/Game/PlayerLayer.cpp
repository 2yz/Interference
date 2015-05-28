#include "PlayerLayer.h"
#include "PlayerUserData.h"

USING_NS_CC;

PlayerLayer::PlayerLayer() :initHP(1000), mPlayer(nullptr), speed(3.0f), moveUp(false), moveDown(false), moveLeft(false), moveRight(false)
{
	visibleSize = Director::getInstance()->getVisibleSize();
    visibleOrigin = Director::getInstance()->getVisibleOrigin();
	positionX = visibleOrigin.x + visibleSize.width / 2;
	positionY = visibleOrigin.y + visibleSize.height / 2;
}

bool PlayerLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	// º‡Ã˝º¸≈Ã ¬º˛
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(PlayerLayer::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(PlayerLayer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	// ªÊ÷∆Player
	mPlayer = Sprite::createWithSpriteFrameName("myPlane.png");
	mPlayer->setAnchorPoint(Vec2(0.5, 0.5));
	mPlayer->setPosition(positionX, positionY);
	mPlayer->setUserData(new PlayerUserData(initHP));
	this->addChild(mPlayer, 0, "PLAYER");
	this->scheduleUpdate();
	return true;
}

cocos2d::Sprite* PlayerLayer::getMyPlane()
{
	return mPlayer;
}

// TODO ≈–∂œ”Œœ∑ «∑Ò‘›Õ£
void PlayerLayer::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	switch (static_cast<int>(keyCode))
	{
	case 146: // W
		moveUp = true;
		break;
	case 142: // S
		moveDown = true;
		break;
	case 124: // A
		moveLeft = true;
		break;
	case 127: // D
		moveRight = true;
		break;
	}
}

void PlayerLayer::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	switch (static_cast<int>(keyCode))
	{
	case 146: // W
		moveUp = false;
		break;
	case 142: // S
		moveDown = false;
		break;
	case 124: // A
		moveLeft = false;
		break;
	case 127: // D
		moveRight = false;
		break;
	}
}

void PlayerLayer::update(float delta)
{
	positionX = mPlayer->getPositionX() + speed*(moveRight - moveLeft);
	positionY = mPlayer->getPositionY() + speed*(moveUp - moveDown);
	if (positionX < visibleOrigin.x + mPlayer->getContentSize().width / 2)
		positionX = visibleOrigin.x + mPlayer->getContentSize().width / 2;
	if (positionX > visibleOrigin.x + visibleSize.width - mPlayer->getContentSize().width / 2)
		positionX = visibleOrigin.x + visibleSize.width - mPlayer->getContentSize().width / 2;
	if (positionY < visibleOrigin.y + mPlayer->getContentSize().height / 2)
		positionY = visibleOrigin.y + mPlayer->getContentSize().height / 2;
	if (positionY > visibleOrigin.y + visibleSize.height - mPlayer->getContentSize().height / 2)
		positionY = visibleOrigin.y + visibleSize.height - mPlayer->getContentSize().height / 2;
	mPlayer->setPosition(positionX, positionY);
}