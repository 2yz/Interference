#include "BattleLayer.h"
#include "ConfigUtil.h"
#include "Controller.h"
#include "GameBackgroundLayer.h"
#include "Bullet.h"
#include "AnimationUtil.h"

USING_NS_CC;

BattleLayer::BattleLayer() : _camera(nullptr), Player(nullptr), initHP(1000), shootTimer(0.0f), shootEnterCD(false)
{
}

BattleLayer::~BattleLayer()
{
	_camera = nullptr;
}

bool BattleLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	// Create Battle Camera
	_camera = Camera::createOrthographic(ConfigUtil::visibleWidth, ConfigUtil::visibleHeight, 0.0f, 1000.0f);
	_camera->setCameraFlag(CameraFlag::USER1);
	_camera->setPosition3D(Vec3((ConfigUtil::battleSceneWidth - ConfigUtil::visibleWidth) / 2, (ConfigUtil::battleSceneHeight - ConfigUtil::visibleHeight) / 2, 400));
	_camera->lookAt(Vec3((ConfigUtil::battleSceneWidth - ConfigUtil::visibleWidth) / 2, (ConfigUtil::battleSceneHeight - ConfigUtil::visibleHeight) / 2, 0));
	this->addChild(_camera);

	// Create Background
	auto gameBackgroundLayer = GameBackgroundLayer::create();
	gameBackgroundLayer->setParent(this);
	this->addChild(gameBackgroundLayer);

	// Create Edge
	auto edgeSp = Sprite::create();
	edgeSp->setTag(EDGE_TAG);
	edgeSp->setParent(this);
	edgeSp->setPosition(ConfigUtil::battleSceneWidth / 2, ConfigUtil::battleSceneHeight / 2);
	auto body = PhysicsBody::createEdgeBox(ConfigUtil::visibleSize * 2, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	body->setGroup(EDGE_GROUP);
	body->setContactTestBitmask(0xFFFFFFFF);
	edgeSp->setPhysicsBody(body);
	this->addChild(edgeSp);

	// Create Player
	Player = Player::create();
	Player->setPosition(ConfigUtil::battleSceneWidth / 2, ConfigUtil::battleSceneHeight / 2);
	this->addChild(Player);

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
    Block1->setPosition(Point(800, 600));
    Block1->setBlendFunc(BlendFunc::ADDITIVE);
    auto tintTo1 = TintTo::create(2.0f, random(0.0f, 255.0f), random(0.0f, 255.0f), random(0.0f, 255.0f));
    Block1->runAction(tintTo1);
	Block1->setCameraMask(1 << 1);
    this->addChild(Block1);
    
    // Run Animation
    AnimationUtil::runParticleAnimation("Cloud.plist", this, Block1);   
    
    // Create Block2
    auto Block2 = Sprite::create();
    Block2->setSpriteFrame("square.png");
    auto body2 = PhysicsBody::createEdgeBox(Block2->getTextureRect().size);
    body2->setContactTestBitmask(0xffffffff);
    Block2->setPhysicsBody(body2);
    Block2->setPosition(Point(1200, 600));
	Block2->setBlendFunc(BlendFunc::ADDITIVE);
    auto tintTo2 = TintTo::create(2.0f, random(0.0f, 255.0f), random(0.0f, 255.0f), random(0.0f, 255.0f));
    Block2->runAction(tintTo2);
	Block2->setCameraMask(1 << 1);
    this->addChild(Block2);
    
    // Run Animation
    AnimationUtil::runParticleAnimation("Death.plist", this, Block2);
    
    return true;
}

Player* BattleLayer::getPlayer()
{
	return Player;
}

void BattleLayer::update(float deltaTime)
{
	this->setCameraMask(1 << 1);
	// log("BattleLayer::update(float deltaTime)");

	// Use Default Camera
	auto positionDelta = Player->getPosition() - Vec2(ConfigUtil::visibleWidth / 2, ConfigUtil::visibleHeight / 2) - _camera->getPosition();
	auto eye = _camera->getPosition3D() + Vec3(positionDelta.x * Player->getTraceCoefficient() * deltaTime, positionDelta.y * Player->getTraceCoefficient() * deltaTime, 0.0f);
	_camera->setPosition3D(eye);
	eye.z = 0.0f;
	_camera->lookAt(eye);

	// Update Shoot Assist
	boxPosition = _camera->getPosition() + Controller::getMouseLocation();
	shootBox->setPosition(boxPosition);
	shootLine->setPosition(Player->getPosition());
	if (boxPosition.x - Player->getPosition().x == 0)
	{
		rotateAngle = 90;
	}
	else
	{
		rotateAngle = atan((boxPosition.y - Player->getPosition().y) / (boxPosition.x - Player->getPosition().x)) / M_PI * 180;
		if (boxPosition.x - Player->getPosition().x < 0)
		{
			rotateAngle += 180;
		}
	}
	shootLine->setRotation(-rotateAngle);

	if (Controller::getMouseDown())
	{
		if (!shootEnterCD)
		{
			auto velocity = boxPosition - Player->getPosition();
			velocity.normalize();
			velocity *= 800;
			auto playerBullet = Bullet::create(velocity);
			playerBullet->setParent(this);
			playerBullet->setPosition(Player->getPosition());
			this->addChild(playerBullet);

			auto scaleToSmall = ScaleTo::create(0.1f, 0.6f);
			auto scaleToBig = ScaleTo::create(0.1f, 1.0f);
			shootBox->runAction(Sequence::create(scaleToSmall, scaleToBig, nullptr));
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

	Node* nodeArray[2][2];
	nodeArray[0][0] = static_cast<Node*>(contact.getShapeA()->getBody()->getNode());
	nodeArray[0][1] = static_cast<Node*>(contact.getShapeB()->getBody()->getNode());
	nodeArray[1][0] = nodeArray[0][1];
	nodeArray[1][1] = nodeArray[0][0];
	// auto nodeA = static_cast<Node*>(contact.getShapeA()->getBody()->getNode());
	// auto nodeB = static_cast<Node*>(contact.getShapeB()->getBody()->getNode());
	// log("CONTACT TEST A: %d B: %d", nodeA->getTag(), nodeB->getTag());

	for (int i = 0; i < 2; ++i)
	{
		if (nodeArray[i][0] != nullptr&&nodeArray != nullptr)
		{
			log("CONTACT TEST TAG: %d", nodeArray[i][0]->getTag());
			switch (nodeArray[i][0]->getTag())
			{
			case BULLET_TAG:
			{
				AnimationUtil::runParticleAnimation("Boom.plist", this, nodeArray[i][0]);
				nodeArray[i][0]->removeFromParentAndCleanup(true);
			}
			break;
			default:
				break;
			}
		}
	}
	return true;
}