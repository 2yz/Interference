#include "BattleLayer.h"
#include "ConfigUtil.h"
#include "Controller.h"
#include "GameBackgroundLayer.h"
#include "AnimationUtil.h"
#include "Block.h"
#include "Enemy.h"

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
	this->addChild(gameBackgroundLayer);

	// Create Edge
	auto edgeBlock = Block::create(true);
	edgeBlock->setPosition(ConfigUtil::visibleSize);
	this->addChild(edgeBlock);

	// Create Player
	player = Player::create();
	player->setPosition(ConfigUtil::battleSceneWidth / 2, ConfigUtil::battleSceneHeight / 2);
	this->addChild(player);

	// Create Shoot Assist Line
	shootLine = Sprite::create("ShootLine.png");
	shootLine->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->addChild(shootLine);

	// Create Block1
	auto block1 = Block::create();
	block1->setPosition(Point(1000, 500));
	this->addChild(block1);

	// Create Block2
	auto block2 = Block::create();
	block2->setPosition(Point(1400, 500));
	this->addChild(block2);

	// Schedule update per frame
	this->scheduleUpdate();

	auto physicsListener = EventListenerPhysicsContact::create();
	physicsListener->onContactBegin = CC_CALLBACK_1(BattleLayer::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(physicsListener, this);

	// schedule(schedule_selector(BattleLayer::addEnemy), 10.0f, 30, 0);
	scheduleOnce(schedule_selector(BattleLayer::addEnemy), 1.0f);
	// addEnemy(0.0f);

	return true;
}

Player* BattleLayer::getPlayer()
{
	return player;
}

void BattleLayer::update(float deltaTime)
{
	// Count Children Nodes
	// log("ChildrenCount %d", this->getChildrenCount());

	// TODO setCameraMask at Every Node
	this->setCameraMask(1 << 1);

	// Use Default Camera
	auto positionDelta = player->getPosition() - Vec2(ConfigUtil::visibleWidth / 2, ConfigUtil::visibleHeight / 2) - _camera->getPosition();
	auto eye = _camera->getPosition3D() + Vec3(positionDelta.x * player->getTraceCoefficient() * deltaTime, positionDelta.y * player->getTraceCoefficient() * deltaTime, 0.0f);
	_camera->setPosition3D(eye);
	eye.z = 0.0f;
	_camera->lookAt(eye);

	mousePositionInLayer = _camera->getPosition() + Controller::getMouseLocation();
	// Update Shoot Assist
	shootLine->setPosition(player->getPosition());
	if (mousePositionInLayer.x - player->getPosition().x == 0)
	{
		shootLineRotateAngle = 90;
	}
	else
	{
		shootLineRotateAngle = atan((mousePositionInLayer.y - player->getPosition().y) / (mousePositionInLayer.x - player->getPosition().x)) / M_PI * 180;
		if (mousePositionInLayer.x - player->getPosition().x < 0)
		{
			shootLineRotateAngle += 180;
		}
	}
	shootLine->setRotation(-shootLineRotateAngle);
	// Launch Skill when Mouse Down
	if (Controller::getMouseDown())
	{
		auto velocity = mousePositionInLayer - player->getPosition();
		velocity.normalize();
		player->runSkill(velocity * 800, ATTACK);
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
		if (nodeArray[i][0] != nullptr&&nodeArray[i][1] != nullptr)
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

void BattleLayer::addEnemy(float deltaTime)
{
	int num = random(4, 9);
	Enemy* enemy;
	for (int i = 0; i < num; ++i)
	{
		enemy = Enemy::create();
		enemy->setPosition(Vec2(random(50.0f, 2000.0f), random(50.0f, 1200.0f)));
		this->addChild(enemy);
		log("ENEMY CONTACT TEST %08X", enemy->getPhysicsBody()->getContactTestBitmask());
	}
}