#include "Player.h"
#include "ConfigUtil.h"
#include "Controller.h"

USING_NS_CC;

Player::Player() : traceCoefficient(0)
{
	velocityMagnitudeMax = 400.0f;
	accelerationMagnitude = 800.0f;
}

bool Player::init()
{
	if (!BasePlane::init())
	{
		return false;
	}

	// Set Camera Trace Cofficient
	this->setTraceCoefficient(velocityMagnitudeMax, accelerationMagnitude, 1.0f / 60.0f);
	
	// Set Physics Body
	physicsBody->setGroup(PLAYER_GROUP);
	physicsBody->setContactTestBitmask(PLAYER_CONTACT_MASK);
	physicsBody->setCollisionBitmask(PLAYER_COLLISION_MASK);
	physicsBody->setCategoryBitmask(PLAYER_CATEGORY_MASK);
	physicsBody->setLinearDamping(1.0f);
	physicsBody->setVelocityLimit(velocityMagnitudeMax);

	// Set Node Tag
	this->setTag(PLAYER_TAG);

	for (auto sprite : spriteVector)
	{
		sprite->setSpriteFrame("triangle.png");
	}

	this->scheduleUpdate();

	return true;
}

void Player::onEnter()
{
	BasePlane::onEnter();
	auto particle = ParticleSystemQuad::create("Tail.plist");
	this->addChild(particle);
}

float Player::getTraceCoefficient()
{
	return traceCoefficient;
}

void Player::setTraceCoefficient(float maxSpeed, float acceleration, float deltaTime)
{
	traceCoefficient = 1.0f / (maxSpeed / acceleration + deltaTime);
}

void Player::update(float deltaTime)
{
	BasePlane::update(deltaTime);
	if ((Controller::getMoveUp() ^ Controller::getMoveDown()) && (Controller::getMoveLeft() ^ Controller::getMoveRight()))
	{
		physicsBody->setVelocity(physicsBody->getVelocity() + accelerationMagnitude * deltaTime *
			Vec2(static_cast<float>(Controller::getMoveRight() - Controller::getMoveLeft()) / static_cast<float>(sqrt(2.0)),
			static_cast<float>(Controller::getMoveUp() - Controller::getMoveDown()) / static_cast<float>(sqrt(2.0))));
	}
	else if (Controller::getMoveUp() || Controller::getMoveDown() || Controller::getMoveLeft() || Controller::getMoveRight())
	{
		physicsBody->setVelocity(physicsBody->getVelocity() + accelerationMagnitude * deltaTime *
			Vec2(static_cast<float>(Controller::getMoveRight() - Controller::getMoveLeft()),
			static_cast<float>(Controller::getMoveUp() - Controller::getMoveDown())));
	}
}
