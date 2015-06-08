#include "BattleLayer.h"
#include "ConfigUtil.h"
#include "Controller.h"
#include "GameBackgroundLayer.h"
#include "Bullet.h"
#include "AnimationUtil.h"

USING_NS_CC;

BattleLayer::BattleLayer() : _camera(nullptr), player(nullptr), initHP(1000)
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
	player = Player::create();
	player->setPosition(ConfigUtil::battleSceneWidth / 2, ConfigUtil::battleSceneHeight / 2);
	this->addChild(player);

	// Create Shoot Assist
	shootBox = Sprite::createWithSpriteFrameName("ShootBox.png");
	this->addChild(shootBox);
	shootLine = Sprite::create("ShootLine.png");
	shootLine->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->addChild(shootLine);
    
    auto Block = Sprite::create();
    Block->setSpriteFrame("square.png");
    auto body1 = PhysicsBody::createEdgeBox(Block->getTextureRect().size);
    Block->setPhysicsBody(body1);
    Block->setPosition(Point(200, 200));
    BlendFunc blend = { GL_SRC_ALPHA, GL_ONE };
    Block->setBlendFunc(blend);
    auto tintTo1 = TintTo::create(2.0f, random(0.0f, 255.0f), random(0.0f, 255.0f), random(0.0f, 255.0f));
    Block->runAction(tintTo1);
    this->addChild(Block);

	// Schedule update per frame
	this->scheduleUpdate();

	auto physicsListener = EventListenerPhysicsContact::create();
	physicsListener->onContactBegin = CC_CALLBACK_1(BattleLayer::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(physicsListener, this);

	return true;
}

Player* BattleLayer::getPlayer()
{
	return player;
}

void BattleLayer::update(float deltaTime)
{
	log("BattleScene Node Num: %zd", this->getChildrenCount());

	this->setCameraMask(1 << 1);
	// log("BattleLayer::update(float deltaTime)");

	// Use Default Camera
	auto positionDelta = player->getPosition() - Vec2(ConfigUtil::visibleWidth / 2, ConfigUtil::visibleHeight / 2) - _camera->getPosition();
	auto eye = _camera->getPosition3D() + Vec3(positionDelta.x * player->getTraceCoefficient() * deltaTime, positionDelta.y * player->getTraceCoefficient() * deltaTime, 0.0f);
	_camera->setPosition3D(eye);
	eye.z = 0.0f;
	_camera->lookAt(eye);

	// Update Shoot Assist
	boxPosition = _camera->getPosition() + Controller::getMouseLocation();
	shootBox->setPosition(boxPosition);
	shootLine->setPosition(player->getPosition());
	if (boxPosition.x - player->getPosition().x == 0)
	{
		rotateAngle = 90;
	}
	else
	{
		rotateAngle = atan((boxPosition.y - player->getPosition().y) / (boxPosition.x - player->getPosition().x)) / M_PI * 180;
		if (boxPosition.x - player->getPosition().x < 0)
		{
			rotateAngle += 180;
		}
	}
	shootLine->setRotation(-rotateAngle);

	if (Controller::getMouseDown())
	{
		auto velocity = boxPosition - player->getPosition();
		velocity.normalize();
		player->runSkill(velocity * 800, ATTACK);

		// Shoot Box Animation
		auto scaleToSmall = ScaleTo::create(0.1f, 0.6f);
		auto scaleToBig = ScaleTo::create(0.1f, 1.0f);
		shootBox->runAction(Sequence::create(scaleToSmall, scaleToBig, nullptr));
	}

}

bool BattleLayer::onContactBegin(cocos2d::PhysicsContact& contact)
{

	BaseObject* nodeArray[2][2];
	nodeArray[0][0] = static_cast<BaseObject*>(contact.getShapeA()->getBody()->getNode());
	nodeArray[0][1] = static_cast<BaseObject*>(contact.getShapeB()->getBody()->getNode());
	nodeArray[1][0] = nodeArray[0][1];
	nodeArray[1][1] = nodeArray[0][0];

	for (int i = 0; i < 2; ++i)
	{
		if (nodeArray[i][0] != nullptr)
		{
			log("CONTACT TEST TAG: %d", nodeArray[i][0]->getTag());
			switch (nodeArray[i][0]->getTag())
			{
			case BULLET_TAG:
				nodeArray[i][0]->onContact(nodeArray[i][1]);
				break;
			default:
				break;
			}
		}
	}
	return true;
}