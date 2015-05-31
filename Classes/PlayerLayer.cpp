/*
* 此类已弃用
*/

#include "PlayerLayer.h"
#include "PlayerUserData.h"
#include "Controller.h"

USING_NS_CC;

PlayerLayer::PlayerLayer() :initHP(1000),acceleration(500.0f),frictionCoefficient(1.0f), maxSpeed(500.0f), speedX(0.0f), speedY(0.0f), playerPositionX(0), playerPositionY(0), mPlayer(nullptr)
{
}

bool PlayerLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	// 绘制Player
	mPlayer = Sprite::createWithSpriteFrameName("myPlane.png");
	mPlayer->setAnchorPoint(Vec2(0.5, 0.5));
	mPlayer->setPosition(playerPositionX, playerPositionY);
	mPlayer->setUserData(new PlayerUserData(initHP));
	this->addChild(mPlayer, 0, "PLAYER");
	this->scheduleUpdate();
	return true;
}

cocos2d::Sprite* PlayerLayer::getMyPlane()
{
	return mPlayer;
}

int PlayerLayer::getInitHP() const
{
	return this->initHP;
}

float PlayerLayer::getPlayerPositionX()
{
	return mPlayer->getPositionX();
}

float PlayerLayer::getPlayerPositionY()
{
	return mPlayer->getPositionY();
}

// void PlayerLayer::setMoveUp(bool value)
// {
// 	this->moveUp = value;
// }
// 
// void PlayerLayer::setMoveDown(bool value)
// {
// 	this->moveDown = value;
// }
// 
// void PlayerLayer::setMoveLeft(bool value)
// {
// 	this->moveLeft = value;
// }
// 
// void PlayerLayer::setMoveRight(bool value)
// {
// 	this->moveRight = value;
// }

// TODO 判断游戏是否暂停

void PlayerLayer::update(float deltaTime)
{
	speedX -= frictionCoefficient * speedX * deltaTime;
	speedY -= frictionCoefficient * speedY * deltaTime;

	if (Controller::getMoveLeft() || Controller::getMoveRight())
	{
		speedX += acceleration * deltaTime *(Controller::getMoveRight() - Controller::getMoveLeft());
		if (speedX > maxSpeed)
			speedX = maxSpeed;
		else if (speedX < -maxSpeed)
			speedX = -maxSpeed;
	}

	if (Controller::getMoveUp() || Controller::getMoveDown())
	{
		speedY += acceleration * deltaTime *(Controller::getMoveUp() - Controller::getMoveDown());
		if (speedY > maxSpeed)
			speedY = maxSpeed;
		else if (speedY < -maxSpeed)
			speedY = -maxSpeed;
	}


	playerPositionX = mPlayer->getPositionX() + speedX * deltaTime;
	playerPositionY = mPlayer->getPositionY() + speedY * deltaTime;
	/*
	if (playerPositionX < visibleOrigin.x + mPlayer->getContentSize().width / 2)
		playerPositionX = visibleOrigin.x + mPlayer->getContentSize().width / 2;
	if (playerPositionX > visibleOrigin.x + visibleSize.width - mPlayer->getContentSize().width / 2)
		playerPositionX = visibleOrigin.x + visibleSize.width - mPlayer->getContentSize().width / 2;
	if (playerPositionY < visibleOrigin.y + mPlayer->getContentSize().height / 2)
		playerPositionY = visibleOrigin.y + mPlayer->getContentSize().height / 2;
	if (playerPositionY > visibleOrigin.y + visibleSize.height - mPlayer->getContentSize().height / 2)
		playerPositionY = visibleOrigin.y + visibleSize.height - mPlayer->getContentSize().height / 2;
	*/
	mPlayer->setPosition(playerPositionX, playerPositionY);
}