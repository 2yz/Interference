#include "BattleLayer.h"
#include "ConfigUtil.h"
#include "Controller.h"
#include "GameBackgroundLayer.h"
#include "Block.h"
#include "Enemy.h"
#include "AudioEngine.h"

USING_NS_CC;

BattleLayer* BattleLayer::battle_layer_ = nullptr;

BattleLayer::BattleLayer() : _timer(0.0f), _camera(nullptr), _player(nullptr), shootLine(nullptr)
{
	battle_layer_ = this;
}

BattleLayer::~BattleLayer()
{
	battle_layer_ = nullptr;
	_camera = nullptr;
	_player = nullptr;
	shootLine = nullptr;
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
	edgeBlock->setPosition(ConfigUtil::border_size_ / 2);
	this->addChild(edgeBlock);

	// Create Player
	if (!_player)
	{
		auto player = Player::create();
		player->setPosition(ConfigUtil::battleSceneWidth / 2, ConfigUtil::battleSceneHeight / 2);
		auto fadeIn = FadeIn::create(1.0f);
		player->runAction(fadeIn);
		this->addChild(player);
	}

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

	schedule(schedule_selector(BattleLayer::addEnemy), 5.0f, 50, 1.0f);
	// scheduleOnce(schedule_selector(BattleLayer::addEnemy), 1.0f);  
	// addEnemy(0.0f);

	// Add BackgroundMusic
	cocos2d::experimental::AudioEngine::play2d("Demo.mp3", true, 0.3f);

	return true;
}

BattleLayer* BattleLayer::getInstance()
{
	return battle_layer_;
}

void BattleLayer::addChild(Node* child)
{
	Layer::addChild(child);
	addLayerChild(child);
}

void BattleLayer::addChild(Node* child, int localZOrder)
{
	Layer::addChild(child, localZOrder);
	addLayerChild(child);
}

void BattleLayer::addLayerChild(Node* child)
{
	switch (child->getTag())
	{
	case PLAYER_TAG:
		if (!_player)
			_player = dynamic_cast<Player*>(child);
		this->enableShootLine();
		break;
	case ENEMY_TAG:
		if (_enemy.empty())
		{
			_enemy.reserve(4);
		}
		_enemy.pushBack(child);
		break;
	case BLOCK_TAG:
		if (_block.empty())
		{
			_block.reserve(4);
		}
		_block.pushBack(child);
		break;
	}
}

void BattleLayer::removeChild(Node* child, bool cleanup)
{
	switch (child->getTag())
	{
	case PLAYER_TAG:
		_player = nullptr;
		disableShootLine();
		break;
	case ENEMY_TAG:
		if (!_enemy.empty())
		{
			auto index = _enemy.getIndex(child);
			if (index != CC_INVALID_INDEX)
				_enemy.erase(index);
		}
		break;
	case BLOCK_TAG:
		if (!_block.empty())
		{
			auto index = _block.getIndex(child);
			if (index != CC_INVALID_INDEX)
				_block.erase(index);
		}
		break;
	}
	Layer::removeChild(child, cleanup);
}

void BattleLayer::removeAllChildrenWithCleanup(bool cleanup)
{
	_player = nullptr;
	_enemy.clear();
	_block.clear();
	Layer::removeAllChildrenWithCleanup(cleanup);
}

cocos2d::Vec2 BattleLayer::getPlayerDirection()
{
	Vec2 direction;
	if (_player != nullptr)
	{
		direction = _camera->getPosition() + Controller::getMouseLocation() - _player->getPosition();
		direction.normalize();
	}
	return direction;
}

cocos2d::Vec2 BattleLayer::getPlayerPosition()
{
	if (_player != nullptr)
		return _player->getPosition();
	return Vec2();
}

void BattleLayer::enableShootLine()
{
	if (_player == nullptr)
		return;
	if (shootLine == nullptr)
	{
		// Create Shoot Assist Line
		shootLine = Sprite::create("ShootLine.png");
		shootLine->setAnchorPoint(Vec2(0.0f, 0.5f));
		this->addChild(shootLine);
	}
	auto fadeIn = FadeIn::create(10.0f);
	shootLine->runAction(fadeIn);
}

void BattleLayer::disableShootLine()
{
	if (shootLine == nullptr)
		return;
	auto fadeOut = FadeOut::create(1.0f);
	shootLine->runAction(fadeOut);
}

void BattleLayer::playerStateMachine()
{
}

void BattleLayer::enemyStateMachine()
{
}

void BattleLayer::addEnemy(float deltaTime)
{
	int num = random(5, 15);
	Enemy* enemy;
	for (int i = 0; i < num; ++i)
	{
		enemy = Enemy::create();
		enemy->setPosition(Vec2(random(40.0f, 1400.0f), random(40.0f, 1400.0f)));
		this->addChild(enemy);
	}
}

bool BattleLayer::onContactBegin(cocos2d::PhysicsContact& contact)
{

	auto nodeA = dynamic_cast<BaseObject*>(contact.getShapeA()->getBody()->getNode());
	auto nodeB = dynamic_cast<BaseObject*>(contact.getShapeB()->getBody()->getNode());
	if (nodeA != nullptr && nodeB != nullptr)
	{
		auto messageA = nodeA->getMessage();
		auto messageB = nodeB->getMessage();
		nodeA->onContact(messageB);
		nodeB->onContact(messageA);
	}
	return true;
}

void BattleLayer::updateCamera(float deltaTime)
{
	if (_player == nullptr)
		return;
	// Use Default Camera
	auto positionDelta = _player->getPosition() - Vec2(ConfigUtil::visibleWidth / 2, ConfigUtil::visibleHeight / 2) - _camera->getPosition();
	auto eye = _camera->getPosition3D() + Vec3(positionDelta.x * _player->getTraceCoefficient() * deltaTime, positionDelta.y * _player->getTraceCoefficient() * deltaTime, 0.0f);
	_camera->setPosition3D(eye);
	eye.z = 0.0f;
	_camera->lookAt(eye);
}

void BattleLayer::updateShootLine(float deltaTime)
{
	if (_player == nullptr)
		return;
	auto mousePositionInLayer = _camera->getPosition() + Controller::getMouseLocation();
	// Update Shoot Assist
	shootLine->setPosition(_player->getPosition());
	float shootLineRotateAngle;
	if (mousePositionInLayer.x - _player->getPosition().x == 0)
	{
		shootLineRotateAngle = 90;
	}
	else
	{
		shootLineRotateAngle = atan((mousePositionInLayer.y - _player->getPosition().y) / (mousePositionInLayer.x - _player->getPosition().x)) / M_PI * 180;
		if (mousePositionInLayer.x - _player->getPosition().x < 0)
		{
			shootLineRotateAngle += 180;
		}
	}
	shootLine->setRotation(-shootLineRotateAngle);

}

void BattleLayer::update(float deltaTime)
{
	_timer += deltaTime*getTimeCoefficient();
	// TODO setCameraMask at Every Node
	this->setCameraMask(1 << 1);
	// Update Camera
	updateCamera(deltaTime);
	// Update ShootLine
	updateShootLine(deltaTime);
}