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
    
    // Create Block
    auto Block = Sprite::create();
    Block->setSpriteFrame("square.png");
    auto body1 = PhysicsBody::createEdgeBox(Block->getTextureRect().size);
    body1->setContactTestBitmask(0xffffffff);
    Block->setPhysicsBody(body1);
    Block->setPosition(Point(200, 200));
    BlendFunc blend = { GL_SRC_ALPHA, GL_ONE };
    Block->setBlendFunc(blend);
    auto tintTo1 = TintTo::create(2.0f, random(0.0f, 255.0f), random(0.0f, 255.0f), random(0.0f, 255.0f));
    Block->runAction(tintTo1);
    this->addChild(Block);

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
			shootEnterCD = true;
			shootTimer = 0.0f;
		}
		else
		{
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
		auto particleA = ParticleSystemQuad::create("Boom.plist");
		particleA->setPosition(nodeA->getPosition());
		this->addChild(particleA);
		nodeA->removeFromParentAndCleanup(true);
	}
	if (nodeB != nullptr && nodeB->getTag() == -2)
	{
		auto particleB = ParticleSystemQuad::create("Boom.plist");
		particleB->setPosition(nodeB->getPosition());
		this->addChild(particleB);
		nodeB->removeFromParentAndCleanup(true);
	}
	

	return true;
}