#include "ControlNode.h"
#include "Controller.h"
#include "ConfigUtil.h"

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

	// gameBackgroundLayer->setAnchorPoint(Vec2(0.5f, 0.5f));
	// gameBackgroundLayer->setPosition(visibleOrigin.x + visibleSize.width / 2, visibleOrigin.y + visibleSize.height / 2);
	// playerLayer->setAnchorPoint(Vec2(0.5f, 0.5f));
	// playerLayer->setPosition(visibleOrigin.x + visibleSize.width / 2, visibleOrigin.y + visibleSize.height / 2);
	// bulletLayer->setAnchorPoint(Vec2(0.5f, 0.5f));
	// bulletLayer->setPosition(visibleOrigin.x + visibleSize.width / 2, visibleOrigin.y + visibleSize.height / 2);
	// enemyBulletLayer->setAnchorPoint(Vec2(0.5f, 0.5f));
	// enemyBulletLayer->setPosition(visibleOrigin.x + visibleSize.width / 2, visibleOrigin.y + visibleSize.height / 2);
	// enemyLayer->setAnchorPoint(Vec2(0.5f, 0.5f));
	// enemyLayer->setPosition(visibleOrigin.x + visibleSize.width / 2, visibleOrigin.y + visibleSize.height / 2);

	this->addChild(gameBackgroundLayer);
	this->addChild(bulletLayer);
	this->addChild(playerLayer);
	this->addChild(enemyBulletLayer);
	this->addChild(enemyLayer);

	// ¼àÌý¼üÅÌÊÂ¼þ
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(ControlNode::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(ControlNode::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

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

void ControlNode::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	switch (keyCode)
	{
		//case 146: // W
	case EventKeyboard::KeyCode::KEY_W:
	case EventKeyboard::KeyCode::KEY_CAPITAL_W:
		// playerLayer->setMoveUp(true);
		Controller::setMoveUp(true);
		break;
		// case 142: // S
	case EventKeyboard::KeyCode::KEY_S:
	case EventKeyboard::KeyCode::KEY_CAPITAL_S:
		// playerLayer->setMoveDown(true);
		Controller::setMoveDown(true);
		break;
		// case 124: // A
	case EventKeyboard::KeyCode::KEY_A:
	case EventKeyboard::KeyCode::KEY_CAPITAL_A:
		// playerLayer->setMoveLeft(true);
		Controller::setMoveLeft(true);
		break;
		// case 127: // D
	case EventKeyboard::KeyCode::KEY_D:
	case EventKeyboard::KeyCode::KEY_CAPITAL_D:
		// playerLayer->setMoveRight(true);
		Controller::setMoveRight(true);
		break;
	}
}

void ControlNode::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	switch (keyCode)
	{
		//case 146: // W
	case EventKeyboard::KeyCode::KEY_W:
	case EventKeyboard::KeyCode::KEY_CAPITAL_W:
		// playerLayer->setMoveUp(false);
		Controller::setMoveUp(false);
		break;
		// case 142: // S
	case EventKeyboard::KeyCode::KEY_S:
	case EventKeyboard::KeyCode::KEY_CAPITAL_S:
		// playerLayer->setMoveDown(false);
		Controller::setMoveDown(false);
		break;
		// case 124: // A
	case EventKeyboard::KeyCode::KEY_A:
	case EventKeyboard::KeyCode::KEY_CAPITAL_A:
		// playerLayer->setMoveLeft(false);
		Controller::setMoveLeft(false);
		break;
		// case 127: // D
	case EventKeyboard::KeyCode::KEY_D:
	case EventKeyboard::KeyCode::KEY_CAPITAL_D:
		// playerLayer->setMoveRight(false);
		Controller::setMoveRight(false);
		break;
	}
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