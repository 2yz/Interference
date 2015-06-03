#include "BattleLayer.h"
#include "ConfigUtil.h"
#include "BulletUserData.h"
#include "EnemyUserData.h"
#include "BattleScene.h"
#include "PlayerUserData.h"
#include "HelloWorldScene.h"
#include "Controller.h"

USING_NS_CC;

BattleLayer::BattleLayer() : playerPlane(nullptr), initHP(1000)
{
}

bool BattleLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	// Create Player
	playerPlane = PlayerPlane::create();
	playerPlane->setPosition(0, 0);
	playerPlane->setUserData(new PlayerUserData(initHP));
	this->addChild(playerPlane);

	// Create Edge
	auto edgeSp = Sprite::create();
	auto body = PhysicsBody::createEdgeBox(ConfigUtil::visibleSize * 2, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	edgeSp->setPosition(Point(0, 0));
	edgeSp->setPhysicsBody(body);
	edgeSp->setTag(0);
	this->addChild(edgeSp);
	
	// Create Shoot Assist
	shootBox = Sprite::createWithSpriteFrameName("ShootBox.png");
	this->addChild(shootBox);
	shootLine = Sprite::create("ShootLine.png");
	shootLine->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->addChild(shootLine);

	// Schedule update per frame
	this->scheduleUpdate();

	return true;
}

PlayerPlane* BattleLayer::getPlayerPlane()
{
	return playerPlane;
}

void BattleLayer::update(float deltaTime)
{
	// log("BattleLayer::update(float deltaTime)");

	// Update Shoot Assist
	boxPosition = Controller::getMouseLocation() - this->getParent()->getPosition();
	shootBox->setPosition(boxPosition);
	shootLine->setPosition(playerPlane->getPosition());
	if (boxPosition.x - playerPlane->getPosition().x == 0)
	{
		rotateAngle = 90;
	}
	else
	{
		rotateAngle = atan((boxPosition.y - playerPlane->getPosition().y) / (boxPosition.x - playerPlane->getPosition().x)) / M_PI * 180;
		if (boxPosition.x - playerPlane->getPosition().x < 0)
		{
			rotateAngle += 180;
		}
	}
	shootLine->setRotation(-rotateAngle);
}