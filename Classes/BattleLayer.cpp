#include "BattleLayer.h"
#include "ConfigUtil.h"
#include "Controller.h"
#include "GameBackgroundLayer.h"
#include "Block.h"
#include "Enemy.h"
#include "AudioEngine.h"
#include "AnimationUtil.h"
#include "CameraNode.h"
#include "Utility.h"
#include "BattleScene.h"
#include "PlayerUserData.h"


USING_NS_CC;

BattleLayer* BattleLayer::battle_layer_ = nullptr;

BattleLayer::BattleLayer() : _timer(0.0f), _player(nullptr), shootLine(nullptr), paused_(false)
{
	battle_layer_ = this;
}

BattleLayer::~BattleLayer()
{
	battle_layer_ = nullptr;
	_player = nullptr;
	shootLine = nullptr;
}

bool BattleLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto physicsListener = EventListenerPhysicsContact::create();
	physicsListener->onContactBegin = CC_CALLBACK_1(BattleLayer::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(physicsListener, this);

	// Keyboard Listener
	auto listenerKeyboard = EventListenerKeyboard::create();
	listenerKeyboard->onKeyPressed = CC_CALLBACK_2(BattleLayer::onKeyPressed, this);
	listenerKeyboard->onKeyReleased = CC_CALLBACK_2(BattleLayer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);

	setListener();

	return true;
}

void BattleLayer::setListener()
{
	auto player_listener = EventListenerCustom::create(PLAYER_EVENT, [=](EventCustom* event)
	{
		PlayerUserData* player_user_data = static_cast<PlayerUserData*>(event->getUserData());
		if (!player_user_data->isAlive())
		{
			setState(LOSS);
			sendBattleEvent(BATTLE_EVENT_LOSE);
		}
	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(player_listener, this);
}

void BattleLayer::onEnter()
{
	Layer::onEnter();
	this->scheduleUpdate();
	enterState(BEGIN);
	background_music = experimental::AudioEngine::play2d(BATTLE_MUSIC, true, BATTLE_MUSIC_VOLUME);
}

void BattleLayer::onExit()
{
	experimental::AudioEngine::stop(background_music);
	Layer::onExit();
}


void BattleLayer::destroyAllObject()
{
	if (_player != nullptr)
		_player->onDestroy();
	for (auto enemy : _enemy)
		enemy->onDestroy();
	for (auto block : _block)
		block->onDestroy();
}

void BattleLayer::pauseLayer()
{
	Layer::pause();
	experimental::AudioEngine::pause(background_music);
	for (auto child : _children)
		child->pause();
	Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(0.0f);
	setTimeCoefficient(0.0f);
	paused_ = true;
}

void BattleLayer::resumeLayer()
{
	Layer::resume();
	experimental::AudioEngine::resume(background_music);
	for (auto child : _children)
		child->resume();
	Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(1.0f);
	setTimeCoefficient(1.0f);
	paused_ = false;
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
	case kPlayerTag:
		if (!_player)
			_player = dynamic_cast<Player*>(child);
		this->enableShootLine();
		break;
	case kEnemyTag:
		if (_enemy.empty())
		{
			_enemy.reserve(4);
		}
		_enemy.pushBack(static_cast<Enemy*>(child));
		break;
	case kBlockTag:
		if (_block.empty())
		{
			_block.reserve(4);
		}
		_block.pushBack(static_cast<Block*>(child));
		break;
	}
}

void BattleLayer::removeChild(Node* child, bool cleanup)
{
	auto child_index = _children.getIndex(child);
	if (child_index != CC_INVALID_INDEX)
	{
		switch (child->getTag())
		{
		case kPlayerTag:
			_player = nullptr;
			disableShootLine();
			break;
		case kEnemyTag:
			if (!_enemy.empty())
			{
				auto index = _enemy.getIndex(static_cast<Enemy*>(child));
				if (index != CC_INVALID_INDEX)
					_enemy.erase(index);
			}
			break;
		case kBlockTag:
			if (!_block.empty())
			{
				auto index = _block.getIndex(static_cast<Block*>(child));
				if (index != CC_INVALID_INDEX)
					_block.erase(index);
			}
			break;
		}
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

bool BattleLayer::isPaused()
{
	return paused_;
}

cocos2d::Vec2 BattleLayer::getPlayerDirection()
{
	Vec2 direction;
	if (_player != nullptr && CameraNode::getCamera() != nullptr)
	{
		direction = CameraNode::getCamera()->getPosition() + Controller::getMouseLocation() - _player->getPosition();
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

void BattleLayer::sendBattleEvent(int event_data)
{
	auto buf = new int(event_data);
	EventCustom battle_event(BATTLE_EVENT);
	battle_event.setUserData(buf);
	_eventDispatcher->dispatchEvent(&battle_event);
	CC_SAFE_DELETE(buf);
}

void BattleLayer::enableShootLine()
{
	if (_player == nullptr)
		return;
	if (shootLine == nullptr)
	{
		// Create Shoot Assist Line
		shootLine = Sprite::createWithSpriteFrameName(kShootLineSpriteFrame);
		shootLine->setAnchorPoint(Vec2(0.0f, 0.5f));
		shootLine->setBlendFunc(BlendFunc::ADDITIVE);
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

void BattleLayer::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_E:
	case EventKeyboard::KeyCode::KEY_CAPITAL_E:
		Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(0.2f);
		setTimeCoefficient(0.2f);
		break;
	default:
		break;
	}
}

void BattleLayer::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_E:
	case EventKeyboard::KeyCode::KEY_CAPITAL_E:
		Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(1.0f);
		setTimeCoefficient(1.0f);
		break;
	default:
		break;
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

void BattleLayer::update(float deltaTime)
{
	_timer += deltaTime*getTimeCoefficient();
	updateStateMachine(deltaTime);
	updateShootLine(deltaTime);
}

void BattleLayer::updateShootLine(float deltaTime)
{
	if (_player == nullptr)
		return;
	auto mousePositionInLayer = CameraNode::getCamera()->getPosition() + Controller::getMouseLocation();
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