#include "BasePlayer.h"
#include "Controller.h"
#include "ConfigUtil.h"

USING_NS_CC;

BasePlayer::BasePlayer() : initHP(1000), acceleration(800.0f), maxSpeed(400.0f)
{
	setTraceCoefficient(maxSpeed, acceleration, 1.0f / 60.0f);
	physicsBody->setContactTestBitmask(PLAYER_CONTACT_MASK);
	physicsBody->setCollisionBitmask(PLAYER_COLLISION_MASK);
	physicsBody->setCategoryBitmask(PLAYER_CATEGORY_MASK);
	physicsBody->setLinearDamping(1.0f);
	physicsBody->setVelocityLimit(maxSpeed);
}

bool BasePlayer::init()
{
	if (!BasePlane::init())
	{
		return false;
	}
	this->setTag(1);
	normalShapeUp->setSpriteFrame("triangle.png");
	auto test = SpriteFrameCache::getInstance()->getSpriteFrameByName("test");
	normalShapeUp->getTextureRect();
	normalShapeDown->setSpriteFrame("triangle.png");
	smallShapeUp->setSpriteFrame("triangle.png");
	smallShapeDown->setSpriteFrame("triangle.png");

	this->scheduleUpdate();
	
	return true;
}

void BasePlayer::update(float deltaTime)
{
	// if ((Controller::getMoveUp() ^ Controller::getMoveDown()) && (Controller::getMoveLeft() ^ Controller::getMoveRight()))
	// {
	// 	physicsBody->setVelocity(physicsBody->getVelocity() + acceleration * deltaTime *
	// 		Vec2(static_cast<float>(Controller::getMoveRight() - Controller::getMoveLeft()) / static_cast<float>(sqrt(2.0)),
	// 		static_cast<float>(Controller::getMoveUp() - Controller::getMoveDown()) / static_cast<float>(sqrt(2.0))));
	// }
	// else if (Controller::getMoveUp() || Controller::getMoveDown() || Controller::getMoveLeft() || Controller::getMoveRight())
	// {
	// 	physicsBody->setVelocity(physicsBody->getVelocity() + acceleration * deltaTime *
	// 		Vec2(static_cast<float>(Controller::getMoveRight() - Controller::getMoveLeft()),
	// 		static_cast<float>(Controller::getMoveUp() - Controller::getMoveDown())));
	// }

	float spriteRotation = normalShapeUp->getRotation() + sqrtf(physicsBody->getVelocity().lengthSquared()) *deltaTime;
	if (spriteRotation > 36000)
		spriteRotation -= 36000;
	normalShapeUp->setRotation(spriteRotation);
	normalShapeDown->setRotation(180.0f - spriteRotation);
	// normalShapeDown->setRotation(-spriteRotation);
	smallShapeUp->setRotation(spriteRotation * 2);
	smallShapeDown->setRotation(180.0f - spriteRotation * 2);
	// smallShapeDown->setRotation(-spriteRotation * 2);

	// log("Velocity X: %f Y: %f", physicsBody->getVelocity().x, physicsBody->getVelocity().y);
	// log("Distance X: %f Y: %f", this->getPositionX() - lastPositionX, this->getPositionY() - lastPositionY);
	// lastPositionX = this->getPositionX();
	// lastPositionY = this->getPositionY();
}