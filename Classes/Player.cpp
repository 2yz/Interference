#include "Player.h"
#include "ConfigUtil.h"
#include "Controller.h"
#include "Attack.h"
#include "BattleLayer.h"
#include "AnimationUtil.h"
#include <AudioEngine.h>

USING_NS_CC;

Player::Player() : _accelerationMagnitude(800.0f)
{
	_HP = 100000.0f;
	_velocityMagnitude = 400.0f;
	linear_damping_ = 1.0f;
	physics_radius_ = 60.0f;
	rotate_velocity_ = 180.0f;
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
		_spriteVector.pushBack(sprite);
		this->addChild(sprite);
	}
	_spriteVector.at(1)->setRotation(180.0f);
	_spriteVector.at(3)->setRotation(180.0f);
	_spriteVector.at(2)->setScale(0.4f);
	_spriteVector.at(3)->setScale(0.4f);
	this->setScale(1.5f);

	// Set Sprite Frame
	for (auto sprite : _spriteVector)
	{
		sprite->setSpriteFrame(kPlayerSpriteFrame);
	}

	// Create Skill
	auto attack = Attack::create();
	addSkill(attack);

	// Set Camera Trace Cofficient
	this->setTraceCoefficient(_velocityMagnitude, _accelerationMagnitude, 1.0f / 60.0f);

	// Set Physics Shape
	_physicsBody->addShape(PhysicsShapeCircle::create(physics_radius_, kPlayerMaterial));

	// Set Node Tag
	this->setTag(kPlayerTag);

	this->scheduleUpdate();

	return true;
}

void Player::initMessage()
{
	_message.putString(kNameKey, kPlayerName);
	_message.putInt(kTagKey, kPlayerTag);
}

void Player::onEnter()
{
	BasePlane::onEnter();

	// Set Physics Body
	_physicsBody->setGroup(kPlayerGroup);
	_physicsBody->setContactTestBitmask(kPlayerContactMask);
	_physicsBody->setCollisionBitmask(kPlayerCollisionMask);
	_physicsBody->setCategoryBitmask(kPlayerCategoryMask);
	_physicsBody->setLinearDamping(linear_damping_);
	_physicsBody->setVelocityLimit(_velocityMagnitude);
}

void Player::onDestroy()
{
	experimental::AudioEngine::play2d(kDeathAudio);
	BasePlane::onDestroy();
}

void Player::onContact(Message& message)
{
	if (message.getInt(kTagKey) == kEnemyTag)
		_HP -= message.getFloat(kDestroyDamageKey);
	else if (message.getInt(kTagKey) == kEnemyBulletTag)
		_HP -= message.getFloat(kDamageKey);
	if (_HP < 0.0f)
		onDestroy();
}

float Player::getTraceCoefficient()
{
	return _traceCoefficient;
}

void Player::setTraceCoefficient(float maxSpeed, float acceleration, float deltaTime)
{
	_traceCoefficient = 1.0f / (maxSpeed / acceleration + deltaTime);
}

void Player::updateMove(float deltaTime)
{
	if ((Controller::getMoveUp() ^ Controller::getMoveDown()) && (Controller::getMoveLeft() ^ Controller::getMoveRight()))
	{
		_physicsBody->setVelocity(_physicsBody->getVelocity() + _accelerationMagnitude * deltaTime *
			Vec2(static_cast<float>(Controller::getMoveRight() - Controller::getMoveLeft()) / static_cast<float>(sqrt(2.0)),
			static_cast<float>(Controller::getMoveUp() - Controller::getMoveDown()) / static_cast<float>(sqrt(2.0))));
	}
	else if (Controller::getMoveUp() || Controller::getMoveDown() || Controller::getMoveLeft() || Controller::getMoveRight())
	{
		_physicsBody->setVelocity(_physicsBody->getVelocity() + _accelerationMagnitude * deltaTime *
			Vec2(static_cast<float>(Controller::getMoveRight() - Controller::getMoveLeft()),
			static_cast<float>(Controller::getMoveUp() - Controller::getMoveDown())));
	}
}

void Player::updateSkillCast(float deltaTime)
{
	if (Controller::getMouseDown())
	{
		auto battle_layer = BattleLayer::getInstance();
		if (battle_layer != nullptr)
			castSkill(battle_layer, battle_layer->getPlayerDirection(), 0);
	}
}

void Player::update(float deltaTime)
{
	deltaTime *= getTimeCoefficient();
	// Sprite Rotation
	float spriteRotation = _spriteVector.at(0)->getRotation() + rotate_velocity_*deltaTime*getTimeCoefficient();
	if (spriteRotation > 360000.0f)
		spriteRotation -= 360000.0f;
	_spriteVector.at(0)->setRotation(spriteRotation);
	_spriteVector.at(1)->setRotation(180.0f - spriteRotation);
	_spriteVector.at(2)->setRotation(spriteRotation * 2.0f);
	_spriteVector.at(3)->setRotation(180.0f - spriteRotation * 2.0f);

	updateMove(deltaTime);
	updateSkillCast(deltaTime);

	BasePlane::update(deltaTime);
}
