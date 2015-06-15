#include "Player.h"
#include "ConfigUtil.h"
#include "Controller.h"
#include "Attack.h"
#include "BattleLayer.h"
#include <SimpleAudioEngine.h>
#include "AnimationUtil.h"

USING_NS_CC;

Player::Player() : _accelerationMagnitude(800.0f)
{
	_HP = 1000.0f;
	_neverDie = false;
	_velocityMagnitude = 400.0f;
	linear_damping_ = 1.0f;
	physics_radius_ = 50.0f;
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
	_spriteVector.at(2)->setScale(0.5f);
	_spriteVector.at(3)->setScale(0.5f);
	this->setScale(0.6f);

	// Set Sprite Frame
	for (auto sprite : _spriteVector)
	{
		sprite->setSpriteFrame(PLAYER_SPRITE_FRAME);
	}

	// Create Skill
	auto attack = Attack::create();
	addSkill(attack);

	// Set Camera Trace Cofficient
	this->setTraceCoefficient(_velocityMagnitude, _accelerationMagnitude, 1.0f / 60.0f);

	// Set Physics Shape
	_physicsBody->addShape(PhysicsShapeCircle::create(physics_radius_, MATERIAL_PLAYER_PLANE));

	// Set Node Tag
	this->setTag(PLAYER_TAG);

	this->scheduleUpdate();

	return true;
}

void Player::initMessage()
{
	_message.putString("Name", "Player");
	_message.putInt("Tag", PLAYER_TAG);
}

void Player::onEnter()
{
	BasePlane::onEnter();

	// Set Physics Body
	_physicsBody->setGroup(PLAYER_GROUP);
	_physicsBody->setContactTestBitmask(PLAYER_CONTACT_MASK);
	_physicsBody->setCollisionBitmask(PLAYER_COLLISION_MASK);
	_physicsBody->setCategoryBitmask(PLAYER_CATEGORY_MASK);
	_physicsBody->setLinearDamping(linear_damping_);
	_physicsBody->setVelocityLimit(_velocityMagnitude);
}

void Player::onDestroy()
{
	auto test = AnimationUtil::runParticleAnimation("Death", this->getParent(), this);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Death.mp3", false, 1.0f);
	BasePlane::onDestroy();
}

void Player::onContact(Message& message)
{
	if (message.getInt("Tag") == ENEMY_TAG)
		_HP -= message.getFloat("DestroyDamage");
	if (message.getInt("Tag") == ENEMY_BULLET_TAG)
		_HP -= message.getFloat("Damage");
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
