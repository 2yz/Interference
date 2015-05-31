#include "CameraNode.h"
#include "Controller.h"
#include "ConfigUtil.h"
#include "GameLayer.h"

USING_NS_CC;

GameBackgroundLayer* CameraNode::gameBackgroundLayer = nullptr;
GameLayer* CameraNode::gameLayer = nullptr;
BulletLayer* CameraNode::bulletLayer = nullptr;
PlayerLayer* CameraNode::playerLayer = nullptr;
EnemyBulletLayer* CameraNode::enemyBulletLayer = nullptr;
EnemyLayer* CameraNode::enemyLayer = nullptr;


CameraNode::CameraNode()
{
}

CameraNode::~CameraNode()
{
	gameBackgroundLayer = nullptr;
	bulletLayer = nullptr;
	playerLayer = nullptr;
	enemyBulletLayer = nullptr;
	enemyLayer = nullptr;
}

bool CameraNode::init()
{
	if (!Node::init())
	{
		return false;
	}
	gameBackgroundLayer = GameBackgroundLayer::create();
	gameBackgroundLayer->setParent(this);
	// playerLayer = PlayerLayer::create();
	// playerLayer->setParent(this);
	// bulletLayer = BulletLayer::create();
	// bulletLayer->setParent(this);
	// enemyBulletLayer = EnemyBulletLayer::create();
	// enemyBulletLayer->setParent(this);
	// enemyLayer = EnemyLayer::create();
	// enemyLayer->setParent(this);
	auto gameLayer = GameLayer::create();
	gameLayer->setParent(this);

	this->addChild(gameBackgroundLayer);
	// this->addChild(bulletLayer);
	// this->addChild(playerLayer);
	// this->addChild(enemyBulletLayer);
	// this->addChild(enemyLayer);
	this->addChild(gameLayer);

	this->scheduleUpdate();

	return true;
}

GameBackgroundLayer* CameraNode::getGameBackgroundLayer()
{
	return this->gameBackgroundLayer;
}

BulletLayer* CameraNode::getBulletLayer()
{
	return this->bulletLayer;
}

PlayerLayer* CameraNode::getPlayerLayer()
{
	return this->playerLayer;
}

EnemyBulletLayer* CameraNode::getEnemyBulletLayer()
{
	return this->enemyBulletLayer;
}

EnemyLayer* CameraNode::getEnemyLayer()
{
	return this->enemyLayer;
}

void CameraNode::update(float deltaTime)
{
	// log("Camera X: %f Y: %f", this->getPositionX(), this->getPositionY());
	// log("Player X: %f Y: %f", gameLayer->getPlayerPlane()->getPositionX(), gameLayer->getPlayerPlane()->getPositionY());
	// log("Veclocity: %f", gameLayer->getPlayerPlane()->getPhysicsBody()->getVelocity().lengthSquared());
	// log("Coefficent: %f", (1 - 1.0f / (gameLayer->getPlayerPlane()->getPhysicsBody()->getVelocity().lengthSquared() / 1000000 + 1)));
	
	auto positionDelta = this->getPosition() - Vec2(ConfigUtil::visibleWidth / 2, ConfigUtil::visibleHeight / 2) + gameLayer->getPlayerPlane()->getPosition();
	log("P Delta X: %f Y: %f", positionDelta.x, positionDelta.y);
	// traceCoefficient = 1.935f = 1 / (planeSpeed / planeAcceleration + deltaTime)
	this->setPosition(this->getPosition() - positionDelta * gameLayer->getPlayerPlane()->getTraceCoefficient() * deltaTime);
	// this->setPosition(this->getPosition() - positionDelta / (gameLayer->getPlayerPlane()->getPhysicsBody()->getVelocity().lengthSquared() / 1000 + 1));

	// Vec2 coefficient;
	// if (abs(gameLayer->getPlayerPlane()->getPositionX() - ConfigUtil::visibleWidth) < ConfigUtil::visibleWidth / 2)
	// {
	// 	coefficient = Vec2(0.1, 1);
	// }
	// if (abs(gameLayer->getPlayerPlane()->getPositionX() + ConfigUtil::visibleWidth) < ConfigUtil::visibleWidth / 2)
	// {
	// 	coefficient = Vec2(0.1, 1);
	// }
	// if (abs(gameLayer->getPlayerPlane()->getPositionY() - ConfigUtil::visibleHeight) < ConfigUtil::visibleHeight / 2)
	// {
	// 	coefficient = Vec2(1, 0.1);
	// }
	// if (abs(gameLayer->getPlayerPlane()->getPositionY() + ConfigUtil::visibleHeight) < ConfigUtil::visibleHeight / 2)
	// {
	// 	coefficient =Vec2(1, 0.1);
	// }
	// positionDelta.set(positionDelta.x*coefficient.x, positionDelta.y*coefficient.y);

	// auto positionOffset = positionDelta * (1 - 1.0f / (positionDelta.lengthSquared() / 100000 + 1));

	// auto offsetValue = 200.0f;
	// auto borderDistanceX = ConfigUtil::visibleWidth - gameLayer->getPlayerPlane()->getPositionX() < gameLayer->getPlayerPlane()->getPositionX() + ConfigUtil::visibleWidth ?
	// 	ConfigUtil::visibleWidth - gameLayer->getPlayerPlane()->getPositionX() : gameLayer->getPlayerPlane()->getPositionX() + ConfigUtil::visibleWidth;
	// auto borderDistanceY = ConfigUtil::visibleHeight - gameLayer->getPlayerPlane()->getPositionY() < gameLayer->getPlayerPlane()->getPositionY() - ConfigUtil::visibleHeight ?
	// 	ConfigUtil::visibleHeight - gameLayer->getPlayerPlane()->getPositionY() : gameLayer->getPlayerPlane()->getPositionY() - ConfigUtil::visibleHeight;
	// borderDistanceX = abs(borderDistanceX) < offsetValue ? 0 : abs(borderDistanceX) - offsetValue;
	// borderDistanceY = abs(borderDistanceY) < offsetValue ? 0 : abs(borderDistanceY) - offsetValue;

	// float offset = 0.0f;
	// if (gameLayer->getPlayerPlane()->getPositionX() < -ConfigUtil::visibleWidth / 2 - offset)
	// {
	// 	// this->setPositionX(ConfigUtil::visibleWidth + offset);
	// 	positionOffset.x = positionDelta.x / (-ConfigUtil::visibleWidth / 2 - offset - gameLayer->getPlayerPlane()->getPositionX() + 1);
	// } 
	// 
	// if (gameLayer->getPlayerPlane()->getPositionX() > ConfigUtil::visibleWidth / 2 + offset)
	// {
	// 	// this->setPositionX(0 - offset);
	// 	positionOffset.x = positionDelta.x / (gameLayer->getPlayerPlane()->getPositionX() - ConfigUtil::visibleWidth / 2 - offset + 1);
	// }
	// if (gameLayer->getPlayerPlane()->getPositionY() < -ConfigUtil::visibleHeight / 2 - offset)
	// {
	// 	// this->setPositionY(ConfigUtil::visibleHeight + offset);
	// 	positionOffset.y = positionDelta.y / (-ConfigUtil::visibleHeight / 2 - offset - gameLayer->getPlayerPlane()->getPositionY() + 1);
	// }
	// if (gameLayer->getPlayerPlane()->getPositionY() > ConfigUtil::visibleHeight / 2 + offset)
	// {
	// 	// this->setPositionY(0 - offset);
	// 	positionOffset.y = positionDelta.y / (gameLayer->getPlayerPlane()->getPositionY() - ConfigUtil::visibleHeight / 2 - offset + 1);
	// }

	// this->setPosition(Vec2(this->getPositionX() - positionDelta.x * (1 - 1 / (positionDelta.lengthSquared() / 100000 + 1)) * (1-1/(borderDistanceX+1)),
	// 	this->getPositionY() - positionDelta.y * (1 - 1 / (positionDelta.lengthSquared() / 100000 + 1)) * (1 - 1 / (borderDistanceY + 1))));

	
	/*
	time += deltaTime;
	float x, y;
	x = this->getPositionX();
	y = this->getPositionY();
	if (time >2 && time <=4)
	{
	this->setPositionX(this->getPositionX() + 2);
	}
	else if (time >4&& time <=6)
	{
	this->setPositionY(this->getPositionY() + 2);
	}
	else if (time >6&&time<=8)
	{
	this->setPositionX(this->getPositionX() - 2);
	}
	else if (time>8 && time <=10)
	{
	this->setPositionY(this->getPositionY() - 2);
	}
	else if (time >10)
	{
	time = 0;
	}
	*/
}