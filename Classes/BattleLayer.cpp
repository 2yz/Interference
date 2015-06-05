#include "BattleLayer.h"
#include "ConfigUtil.h"
#include "PlayerUserData.h"
#include "Controller.h"
#include "PlayerBullet.h"
#include "AnimationUtil.h"

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
    
    // Create Block1
    auto Block1 = Sprite::create();
    Block1->setSpriteFrame("square.png");
    auto body1 = PhysicsBody::createEdgeBox(Block1->getTextureRect().size);
    body1->setContactTestBitmask(0xffffffff);
    Block1->setPhysicsBody(body1);
    Block1->setPosition(Point(200, 200));
    BlendFunc blend = { GL_SRC_ALPHA, GL_ONE };
    Block1->setBlendFunc(blend);
    auto tintTo1 = TintTo::create(2.0f, random(0.0f, 255.0f), random(0.0f, 255.0f), random(0.0f, 255.0f));
    Block1->runAction(tintTo1);
    this->addChild(Block1);
    
    // Run Animation
    AnimationUtil::runParticleAnimation("Birth.plist", this, Block1);
    AnimationUtil::runParticleAnimation("Cloud.plist", this, Block1);
    
    

    // Create Block2
    auto Block2 = Sprite::create();
    Block2->setSpriteFrame("square.png");
    auto body2 = PhysicsBody::createEdgeBox(Block2->getTextureRect().size);
    body2->setContactTestBitmask(0xffffffff);
    Block2->setPhysicsBody(body1);
    Block2->setPosition(Point(500, 200));
    BlendFunc blend2 = { GL_SRC_ALPHA, GL_ONE };
    Block2->setBlendFunc(blend2);
    auto tintTo2 = TintTo::create(2.0f, random(0.0f, 255.0f), random(0.0f, 255.0f), random(0.0f, 255.0f));
    Block2->runAction(tintTo2);
    this->addChild(Block2);
    
    // Run Animation
    auto iLoop = AnimationUtil::runParticleAnimation("Death.plist", this, Block2);
    
    
    
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
        AnimationUtil::runParticleAnimation("Birth.plist", this, nodeA);
        AnimationUtil::runParticleAnimation("Cloud.plist", this, nodeA);
		nodeA->removeFromParentAndCleanup(true);
	}
	if (nodeB != nullptr && nodeB->getTag() == -2)
	{
        AnimationUtil::runParticleAnimation("Birth.plist", this, nodeB);
        AnimationUtil::runParticleAnimation("Cloud.plist", this, nodeB);
		nodeB->removeFromParentAndCleanup(true);
	}
	

	return true;
}