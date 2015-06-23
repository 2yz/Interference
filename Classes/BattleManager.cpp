#include "BattleManager.h"
#include "ConfigUtil.h"
#include "Controller.h"
#include "Block.h"
#include "Enemy.h"
#include "AudioEngine.h"
#include "CameraManager.h"
#include "PlayerUserData.h"

USING_NS_CC;

BattleManager* BattleManager::battle_layer_ = nullptr;

BattleManager::BattleManager() : timer_(0.0f), player_(nullptr), shoot_line_(nullptr), paused_(false)
{
	battle_layer_ = this;
}

BattleManager::~BattleManager()
{
	battle_layer_ = nullptr;
	player_ = nullptr;
	shoot_line_ = nullptr;
}

bool BattleManager::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto physicsListener = EventListenerPhysicsContact::create();
	physicsListener->onContactBegin = CC_CALLBACK_1(BattleManager::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(physicsListener, this);

	// Keyboard Listener
	auto listenerKeyboard = EventListenerKeyboard::create();
	listenerKeyboard->onKeyPressed = CC_CALLBACK_2(BattleManager::onKeyPressed, this);
	listenerKeyboard->onKeyReleased = CC_CALLBACK_2(BattleManager::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);
	
	this->scheduleUpdate();
	setListener();

	return true;
}

void BattleManager::setListener()
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

void BattleManager::onEnter()
{
	Layer::onEnter();
	enterState(BEGIN);
	background_music_ = experimental::AudioEngine::play2d(BATTLE_MUSIC, true, BATTLE_MUSIC_VOLUME);
}

void BattleManager::onExit()
{
	experimental::AudioEngine::stop(background_music_);
	Layer::onExit();
}

void BattleManager::pauseLayer()
{
	Layer::pause();
	experimental::AudioEngine::pause(background_music_);
	for (auto child : _children)
		child->pause();
	Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(0.0f);
	setTimeCoefficient(0.0f);
	paused_ = true;
}

void BattleManager::resumeLayer()
{
	Layer::resume();
	experimental::AudioEngine::resume(background_music_);
	for (auto child : _children)
		child->resume();
	Director::getInstance()->getRunningScene()->getPhysicsWorld()->setSpeed(1.0f);
	setTimeCoefficient(1.0f);
	paused_ = false;
}


BattleManager* BattleManager::getInstance()
{
	return battle_layer_;
}

void BattleManager::addChild(Node* child)
{
	Layer::addChild(child);
	addLayerChild(child);
}

void BattleManager::addChild(Node* child, int localZOrder)
{
	Layer::addChild(child, localZOrder);
	addLayerChild(child);
}

void BattleManager::addLayerChild(Node* child)
{
	switch (child->getTag())
	{
	case kPlayerTag:
		if (!player_)
			player_ = dynamic_cast<Player*>(child);
		this->enableShootLine();
		break;
	case kEnemyTag:
		if (enemy_.empty())
		{
			enemy_.reserve(4);
		}
		enemy_.pushBack(static_cast<Enemy*>(child));
		break;
	case kBlockTag:
		if (block_.empty())
		{
			block_.reserve(4);
		}
		block_.pushBack(static_cast<Block*>(child));
		break;
	}
}

void BattleManager::removeChild(Node* child, bool cleanup)
{
	auto child_index = _children.getIndex(child);
	if (child_index != CC_INVALID_INDEX)
	{
		switch (child->getTag())
		{
		case kPlayerTag:
			player_ = nullptr;
			disableShootLine();
			break;
		case kEnemyTag:
			if (!enemy_.empty())
			{
				auto index = enemy_.getIndex(static_cast<Enemy*>(child));
				if (index != CC_INVALID_INDEX)
					enemy_.erase(index);
			}
			break;
		case kBlockTag:
			if (!block_.empty())
			{
				auto index = block_.getIndex(static_cast<Block*>(child));
				if (index != CC_INVALID_INDEX)
					block_.erase(index);
			}
			break;
		}
	}
	Layer::removeChild(child, cleanup);
}

void BattleManager::removeAllChildrenWithCleanup(bool cleanup)
{
	player_ = nullptr;
	enemy_.clear();
	block_.clear();
	Layer::removeAllChildrenWithCleanup(cleanup);
}

bool BattleManager::isPaused()
{
	return paused_;
}

cocos2d::Vec2 BattleManager::getPlayerDirection()
{
	Vec2 direction;
	if (player_ != nullptr && CameraManager::getCamera() != nullptr)
	{
		direction = CameraManager::getCamera()->getPosition() + Controller::getMouseLocation() - player_->getPosition();
		direction.normalize();
	}
	return direction;
}

cocos2d::Vec2 BattleManager::getPlayerPosition()
{
	if (player_ != nullptr)
		return player_->getPosition();
	return Vec2();
}

void BattleManager::sendBattleEvent(int event_data)
{
	auto buf = new int(event_data);
	EventCustom battle_event(BATTLE_EVENT);
	battle_event.setUserData(buf);
	_eventDispatcher->dispatchEvent(&battle_event);
	CC_SAFE_DELETE(buf);
}

void BattleManager::sendDestroyEvent()
{
	// std::vector<BaseEnemy*> enemy_vector;
	// for (auto enemy : enemy_)
	// 	enemy_vector.push_back(enemy);
	// for (auto enemy : enemy_vector)
	// 	enemy->onDestroy();
	auto buf = new int(DESTROY_EVENT_ALL);
	EventCustom battle_event(DESTROY_EVENT);
	battle_event.setUserData(buf);
	_eventDispatcher->dispatchEvent(&battle_event);
	CC_SAFE_DELETE(buf);
}

void BattleManager::enableShootLine()
{
	if (player_ == nullptr)
		return;
	if (shoot_line_ == nullptr)
	{
		// Create Shoot Assist Line
		shoot_line_ = Sprite::createWithSpriteFrameName(SHOOT_LINE_SPRITE_FRAME);
		shoot_line_->setAnchorPoint(Vec2(0.0f, 0.5f));
		shoot_line_->setBlendFunc(BlendFunc::ADDITIVE);
		this->addChild(shoot_line_);
	}
	auto fadeIn = FadeIn::create(10.0f);
	shoot_line_->runAction(fadeIn);
}

void BattleManager::disableShootLine()
{
	if (shoot_line_ == nullptr)
		return;
	auto fadeOut = FadeOut::create(1.0f);
	shoot_line_->runAction(fadeOut);
}

void BattleManager::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
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

void BattleManager::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
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

bool BattleManager::onContactBegin(cocos2d::PhysicsContact& contact)
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

void BattleManager::update(float delta_time)
{
	timer_ += delta_time*getTimeCoefficient();
	updateStateMachine(delta_time);
	updateShootLine(delta_time);
}

void BattleManager::updateShootLine(float delta_time)
{
	if (player_ == nullptr)
		return;
	auto mousePositionInLayer = CameraManager::getCamera()->getPosition() + Controller::getMouseLocation();
	// Update Shoot Assist
	shoot_line_->setPosition(player_->getPosition());
	float shootLineRotateAngle;
	if (mousePositionInLayer.x - player_->getPosition().x == 0)
	{
		shootLineRotateAngle = 90;
	}
	else
	{
		shootLineRotateAngle = atan((mousePositionInLayer.y - player_->getPosition().y) / (mousePositionInLayer.x - player_->getPosition().x)) / M_PI * 180;
		if (mousePositionInLayer.x - player_->getPosition().x < 0)
		{
			shootLineRotateAngle += 180;
		}
	}
	shoot_line_->setRotation(-shootLineRotateAngle);
}