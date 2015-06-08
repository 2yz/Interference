#include "Player.h"
#include "ConfigUtil.h"
#include "Controller.h"
#include "Attack.h"

USING_NS_CC;

Player::Player() : traceCoefficient(0)
{
	_velocityMagnitudeMax = 400.0f;
	_accelerationMagnitude = 800.0f;
	_HP = 2000.0f;
	_physicsRadius = 60.0f;
	_rotateVelocity = 180.0f;
}

bool Player::init()
{
	if (!BasePlane::init())
	{
		return false;
	}

	// Create Sprite
	auto sprite1 = Sprite::create();
	auto sprite2 = Sprite::create();
	auto sprite3 = Sprite::create();
	auto sprite4 = Sprite::create();
	sprite2->setRotation(180.0f);
	sprite4->setRotation(180.0f);
	sprite3->setScale(0.2f);
	sprite4->setScale(0.2f);
	_spriteVector.pushBack(sprite1);
	_spriteVector.pushBack(sprite2);
	_spriteVector.pushBack(sprite3);
	_spriteVector.pushBack(sprite4);
	this->addChild(sprite1);
	this->addChild(sprite2);
	this->addChild(sprite3);
	this->addChild(sprite4);
	// Set Sprite Frame
	for (auto sprite : _spriteVector)
	{
		sprite->setSpriteFrame("hexagon.png");
	}

	// Create Skill
	auto attack = Attack::create();
	_skillVec.pushBack(attack);
	this->addChild(attack);

	// Set Camera Trace Cofficient
	this->setTraceCoefficient(_velocityMagnitudeMax, _accelerationMagnitude, 1.0f / 60.0f);

	// Set Physics Shape
	_physicsBody->addShape(PhysicsShapeCircle::create(_physicsRadius, MATERIAL_PLANE));

	// Set Node Tag
	this->setTag(PLAYER_TAG);

	this->scheduleUpdate();

	return true;
}

void Player::onEnter()
{
	BasePlane::onEnter();

	// Set Physics Body
	_physicsBody->setGroup(PLAYER_GROUP);
	_physicsBody->setContactTestBitmask(PLAYER_CONTACT_MASK);
	_physicsBody->setCollisionBitmask(PLAYER_COLLISION_MASK);
	_physicsBody->setCategoryBitmask(PLAYER_CATEGORY_MASK);
	_physicsBody->setLinearDamping(1.0f);
	_physicsBody->setVelocityLimit(_velocityMagnitudeMax);

	auto particle = ParticleSystemQuad::create("Tail.plist");
	this->addChild(particle);
	for (auto sprite : _spriteVector)
	{
		sprite->setColor(Color3B(128, 0, 0));
	}
}

float Player::getTraceCoefficient()
{
	return traceCoefficient;
}

void Player::setTraceCoefficient(float maxSpeed, float acceleration, float deltaTime)
{
	traceCoefficient = 1.0f / (maxSpeed / acceleration + deltaTime);
}

void Player::runSkill(const cocos2d::Vec2& velocity, SkillCategory skillCategory, int skillIndex)
{
	BasePlane::runSkill(velocity, skillCategory, skillIndex);
	for (auto skill : _skillVec)
	{
		if (skill->getSkillCategory() == skillCategory)
		{
			if (skillIndex == 0)
			{
				skill->run(velocity, this->getParent(), this);
			}
			else
			{
				--skillIndex;
			}
		}
	}
}

void Player::update(float deltaTime)
{
	BasePlane::update(deltaTime);

	// Sprite Rotation
	float spriteRotation = _spriteVector.at(0)->getRotation() + _rotateVelocity*deltaTime*getTimeCoefficient();
	if (spriteRotation > 360000.0f)
		spriteRotation -= 360000.0f;
	_spriteVector.at(0)->setRotation(spriteRotation);
	_spriteVector.at(1)->setRotation(180.0f - spriteRotation);
	_spriteVector.at(2)->setRotation(spriteRotation * 2.0f);
	_spriteVector.at(3)->setRotation(180.0f - spriteRotation * 2.0f);

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
