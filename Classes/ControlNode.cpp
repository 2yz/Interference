#include "ControlNode.h"
#include "Controller.h"
#include "ConfigUtil.h"
#include "GameLayer.h"

USING_NS_CC;

GameBackgroundLayer* ControlNode::gameBackgroundLayer = nullptr;
BulletLayer* ControlNode::bulletLayer = nullptr;
PlayerLayer* ControlNode::playerLayer = nullptr;
EnemyBulletLayer* ControlNode::enemyBulletLayer = nullptr;
EnemyLayer* ControlNode::enemyLayer = nullptr;


ControlNode::ControlNode()
{
}

ControlNode::~ControlNode()
{
	gameBackgroundLayer = nullptr;
	bulletLayer = nullptr;
	playerLayer = nullptr;
	enemyBulletLayer = nullptr;
	enemyLayer = nullptr;
}

bool ControlNode::init()
{
	if (!Node::init())
	{
		return false;
	}
	gameBackgroundLayer = GameBackgroundLayer::create();
	gameBackgroundLayer->setParent(this);
	playerLayer = PlayerLayer::create();
	playerLayer->setParent(this);
	bulletLayer = BulletLayer::create();
	bulletLayer->setParent(this);
	enemyBulletLayer = EnemyBulletLayer::create();
	enemyBulletLayer->setParent(this);
	enemyLayer = EnemyLayer::create();
	enemyLayer->setParent(this);
	auto gameLayer = GameLayer::create();
	gameLayer->setParent(this);

	this->addChild(gameBackgroundLayer);
	this->addChild(bulletLayer);
	this->addChild(playerLayer);
	this->addChild(enemyBulletLayer);
	this->addChild(enemyLayer);

	this->addChild(gameLayer);

	

	this->scheduleUpdate();

	return true;
}

GameBackgroundLayer* ControlNode::getGameBackgroundLayer()
{
	return this->gameBackgroundLayer;
}

BulletLayer* ControlNode::getBulletLayer()
{
	return this->bulletLayer;
}

PlayerLayer* ControlNode::getPlayerLayer()
{
	return this->playerLayer;
}

EnemyBulletLayer* ControlNode::getEnemyBulletLayer()
{
	return this->enemyBulletLayer;
}

EnemyLayer* ControlNode::getEnemyLayer()
{
	return this->enemyLayer;
}

void ControlNode::update(float delta)
{
	log("Camera X: %f Y: %f", this->getPositionX(), this->getPositionY());
	log("Player X: %f Y: %f", playerLayer->getPlayerPositionX(), playerLayer->getPlayerPositionY());
	log("P in C X: %f Y: %f", this->getPositionX() - ConfigUtil::visibleWidth / 2 - playerLayer->getPlayerPositionX(), this->getPositionY() - ConfigUtil::visibleHeight / 2 - playerLayer->getPlayerPositionY());
	/*
	time += delta;
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