#include "Player.h"
#include "ConfigUtil.h"
#include "Controller.h"
#include "Attack.h"
#include "BattleManager.h"
#include "AudioEngine.h"
#include "PlayerUserData.h"

USING_NS_CC;

Player::Player() : acceleration_magnitude_(800.0f)
{
	hp_ = 200.0f;
	hp_max_ = 200.0f;
	velocity_magnitude_ = 400.0f;
	linear_damping_ = 1.0f;
	physics_radius_ = 50.0f;
	rotate_velocity_ = 180.0f;
}

Player::~Player()
{
	CC_SAFE_DELETE(_userData);
}

bool Player::init()
{
	if (!BasePlane::init())
	{
		return false;
	}

	// Create Sprite
	for (int i = 0; i < 4; ++i)
	{
		auto sprite = Sprite::create();
		sprite_vector_.pushBack(sprite);
		this->addChild(sprite);
	}
	sprite_vector_.at(1)->setRotation(180.0f);
	sprite_vector_.at(3)->setRotation(180.0f);
	sprite_vector_.at(2)->setScale(0.4f);
	sprite_vector_.at(3)->setScale(0.4f);
	this->setScale(0.8f);

	// Set Sprite Frame
	for (auto sprite : sprite_vector_)
	{
		sprite->setSpriteFrame(PLAYER_SPRITE_FRAME);
	}

	// Create Skill
	auto attack = Attack::create();
	addSkill(attack);

	// Set Camera Trace Cofficient
	this->setTraceCoefficient(velocity_magnitude_, acceleration_magnitude_, 1.0f / 60.0f);

	// Set Physics Shape
	physics_body_->addShape(PhysicsShapeCircle::create(physics_radius_, kPlayerMaterial));

	// Set Node Tag
	this->setTag(kPlayerTag);

	// Set Player User Data
	setUserData(new PlayerUserData(hp_, hp_max_));

	this->scheduleUpdate();

	return true;
}

void Player::initMessage()
{
	message_.putString(kNameKey, kPlayerName);
	message_.putInt(kTagKey, kPlayerTag);
}

void Player::onEnter()
{
	BasePlane::onEnter();

	// Set Physics Body
	physics_body_->setGroup(kPlayerGroup);
	physics_body_->setContactTestBitmask(kPlayerContactMask);
	physics_body_->setCollisionBitmask(kPlayerCollisionMask);
	physics_body_->setCategoryBitmask(kPlayerCategoryMask);
	physics_body_->setLinearDamping(linear_damping_);
	physics_body_->setVelocityLimit(velocity_magnitude_);
}

void Player::onDestroy()
{
	experimental::AudioEngine::play2d(DEATH_AUDIO);
	BasePlane::onDestroy();
}

void Player::onContact(Message& message)
{
	if (message.getInt(kTagKey) == kEnemyTag)
		hp_ -= message.getFloat(kDestroyDamageKey);
	else if (message.getInt(kTagKey) == kEnemyBulletTag)
		hp_ -= message.getFloat(kDamageKey);
	if (_userData != nullptr)
	{
		static_cast<PlayerUserData*>(_userData)->setHP(hp_);
		EventCustom event(PLAYER_EVENT);
		event.setUserData(_userData);
		_eventDispatcher->dispatchEvent(&event);
	}
	if (hp_ <= 0.0f)
		onDestroy();
}

float Player::getTraceCoefficient()
{
	return trace_coefficient_;
}

void Player::setTraceCoefficient(float maxSpeed, float acceleration, float delta_time)
{
	trace_coefficient_ = 1.0f / (maxSpeed / acceleration + delta_time);
}

void Player::updateMove(float delta_time)
{
	if ((Controller::getMoveUp() ^ Controller::getMoveDown()) && (Controller::getMoveLeft() ^ Controller::getMoveRight()))
	{
		physics_body_->setVelocity(physics_body_->getVelocity() + acceleration_magnitude_ * delta_time *
			Vec2(static_cast<float>(Controller::getMoveRight() - Controller::getMoveLeft()) / static_cast<float>(sqrt(2.0)),
			static_cast<float>(Controller::getMoveUp() - Controller::getMoveDown()) / static_cast<float>(sqrt(2.0))));
	}
	else if (Controller::getMoveUp() || Controller::getMoveDown() || Controller::getMoveLeft() || Controller::getMoveRight())
	{
		physics_body_->setVelocity(physics_body_->getVelocity() + acceleration_magnitude_ * delta_time *
			Vec2(static_cast<float>(Controller::getMoveRight() - Controller::getMoveLeft()),
			static_cast<float>(Controller::getMoveUp() - Controller::getMoveDown())));
	}
	EventCustom event(CAMERA_EVENT);
	event.setUserData(this);
	_eventDispatcher->dispatchEvent(&event);
}

void Player::updateSkillCast(float delta_time)
{
	if (Controller::getMouseDown())
	{
		auto battle_manager = BattleManager::getInstance();
		if (battle_manager != nullptr)
			castSkill(battle_manager, battle_manager->getPlayerDirection(), 0);
	}
}

void Player::update(float delta_time)
{
	delta_time *= getTimeCoefficient();
	// Sprite Rotation
	float spriteRotation = sprite_vector_.at(0)->getRotation() + rotate_velocity_*delta_time*getTimeCoefficient();
	if (spriteRotation > 360000.0f)
		spriteRotation -= 360000.0f;
	sprite_vector_.at(0)->setRotation(spriteRotation);
	sprite_vector_.at(1)->setRotation(180.0f - spriteRotation);
	sprite_vector_.at(2)->setRotation(spriteRotation * 2.0f);
	sprite_vector_.at(3)->setRotation(180.0f - spriteRotation * 2.0f);

	updateMove(delta_time);
	updateSkillCast(delta_time);

	BasePlane::update(delta_time);
}
