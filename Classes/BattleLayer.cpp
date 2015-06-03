#include "BattleLayer.h"
#include "ConfigUtil.h"
#include "PlayerUserData.h"
#include "Controller.h"
#include "PlayerBullet.h"

USING_NS_CC;

BattleLayer::BattleLayer() : playerPlane(nullptr), initHP(1000), shootTimer(0.0f), shootEnterCD(false)
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
	body->setContactTestBitmask(0xFFFFFFFF);
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

	auto physicsListener = EventListenerPhysicsContact::create();
	physicsListener->onContactBegin = CC_CALLBACK_1(BattleLayer::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(physicsListener, this);

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

	if (Controller::getMouseDown())
	{
		if (!shootEnterCD)
		{
			auto velocity = boxPosition - playerPlane->getPosition();
			velocity.normalize();
			velocity *= 800;
			auto playerBullet = PlayerBullet::create(velocity);
			playerBullet->setPosition(playerPlane->getPosition());
			this->addChild(playerBullet);
			auto scaleToSmall = ScaleTo::create(0.1f, 0.6f);
			auto scaleToBig = ScaleTo::create(0.1f, 1.0f);
			shootBox->runAction(Sequence::create(scaleToSmall,scaleToBig,nullptr));
			// shootBox->setScale(random(0.6f,0.6f));
			shootEnterCD = true;
			shootTimer = 0.0f;

		}
		else
		{
			// shootBox->setScale(1.0f);
			shootTimer += deltaTime;
			if (shootTimer >= shootCD)
				shootEnterCD = false;
		}

	}
}

bool BattleLayer::onContactBegin(cocos2d::PhysicsContact& contact)
{
	auto nodeA = static_cast<Node*>(contact.getShapeA()->getBody()->getNode());
	auto nodeB = static_cast<Node*>(contact.getShapeB()->getBody()->getNode());

	// log("CONTACT TEST A: %d B: %d", nodeA->getTag(), nodeB->getTag());

	if (nodeA != nullptr && nodeA->getTag() == -2)
	{
		log("CONTACT TEST A: %d", nodeA->getTag());
		auto particleA = ParticleSystemQuad::create("Boom.plist");
		particleA->setPosition(nodeA->getPosition());
		this->addChild(particleA);
		nodeA->removeFromParentAndCleanup(true);
	}
	if (nodeB != nullptr &&nodeB->getTag() == -2)
	{
		log("CONTACT TEST B: %d", nodeB->getTag());
		auto particleB = ParticleSystemQuad::create("Boom.plist");
		particleB->setPosition(nodeB->getPosition());
		this->addChild(particleB);
		nodeB->removeFromParentAndCleanup(true);
	}


	return true;
}