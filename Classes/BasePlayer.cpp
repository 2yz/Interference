#include "BasePlayer.h"
#include "Controller.h"
#include "ConfigUtil.h"

USING_NS_CC;

BasePlayer::BasePlayer()
{
	velocityMagnitudeMax = 400.0f;
	accelerationMagnitude = 800.0f;
	setTraceCoefficient(velocityMagnitudeMax, accelerationMagnitude, 1.0f / 60.0f);
	physicsBody->setGroup(PLAYER_GROUP);
	physicsBody->setContactTestBitmask(PLAYER_CONTACT_MASK);
	physicsBody->setCollisionBitmask(PLAYER_COLLISION_MASK);
	physicsBody->setCategoryBitmask(PLAYER_CATEGORY_MASK);
	physicsBody->setLinearDamping(1.0f);
	physicsBody->setVelocityLimit(velocityMagnitudeMax);
}

bool BasePlayer::init()
{
	if (!BasePlane::init())
	{
		return false;
	}
	this->setTag(PLAYER_GROUP);
	for (auto sprite : spriteVector)
	{
		sprite->setSpriteFrame("triangle.png");
	}
	for (auto extraSprite : extraSpriteVector)
	{
		extraSprite->setSpriteFrame("triangle.png");
	}
	this->scheduleUpdate();	
	return true;
}

void BasePlayer::update(float deltaTime)
{
	BasePlane::update(deltaTime);
	// log("rotation %f", spriteVector.at(0)->getRotation());
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

	// Make Sprite Rotate
	// float spriteRotation = normalShapeUp->getRotation() + sqrtf(physicsBody->getVelocity().lengthSquared()) *deltaTime;
	// if (spriteRotation > 36000)
	// 	spriteRotation -= 36000;
	// normalShapeUp->setRotation(spriteRotation);
	// normalShapeDown->setRotation(180.0f - spriteRotation);
	// smallShapeUp->setRotation(spriteRotation * 2);
	// smallShapeDown->setRotation(180.0f - spriteRotation * 2);

	// log("Velocity X: %f Y: %f", physicsBody->getVelocity().x, physicsBody->getVelocity().y);
	// log("Distance X: %f Y: %f", this->getPositionX() - lastPositionX, this->getPositionY() - lastPositionY);
	// lastPositionX = this->getPositionX();
	// lastPositionY = this->getPositionY();
}