#include "PlayerPlane.h"
#include "Controller.h"

USING_NS_CC;

PlayerPlane::PlayerPlane() : initHP(1000), acceleration(800.0f), maxSpeed(400.0f), traceCoefficient(1 / (maxSpeed / acceleration + 1.0f / 60.0f))
{
	log("PlayerPlane()");
	physicsBody->setContactTestBitmask(0xFFFFFFFF);
	physicsBody->setLinearDamping(1.0f);
	physicsBody->setVelocityLimit(maxSpeed);
}

bool PlayerPlane::init()
{
	if (!BasePlane::init())
	{
		return false;
	}
	this->scheduleUpdate();
	return true;
}

// PlayerPlane* PlayerPlane::create()
// {
// 	PlayerPlane* pRet = new(std::nothrow) PlayerPlane();
// 	CALL_INIT();
// }

void PlayerPlane::update(float deltaTime)
{
	// log("LinearDamping: %f", physicsBody->getLinearDamping());
	// log("PlayerPlane X: %f Y: %f", this->getPositionX(), this->getPositionY());
	if ((Controller::getMoveUp() ^ Controller::getMoveDown()) && (Controller::getMoveLeft() ^ Controller::getMoveRight()))
	{
		physicsBody->setVelocity(physicsBody->getVelocity() + acceleration * deltaTime *
			Vec2(static_cast<float>(Controller::getMoveRight() - Controller::getMoveLeft()) / static_cast<float>(sqrt(2.0)),
			static_cast<float>(Controller::getMoveUp() - Controller::getMoveDown()) / static_cast<float>(sqrt(2.0))));
	}
	else if (Controller::getMoveUp() || Controller::getMoveDown() || Controller::getMoveLeft() || Controller::getMoveRight())
	{
		physicsBody->setVelocity(physicsBody->getVelocity() + acceleration * deltaTime *
			Vec2(static_cast<float>(Controller::getMoveRight() - Controller::getMoveLeft()),
			static_cast<float>(Controller::getMoveUp() - Controller::getMoveDown())));
	}
	log("Velocity X: %f Y: %f", physicsBody->getVelocity().x, physicsBody->getVelocity().y);
	log("Distance X: %f Y: %f", this->getPositionX() - lastPositionX, this->getPositionY() - lastPositionY);
	lastPositionX = this->getPositionX();
	lastPositionY = this->getPositionY();
}

float PlayerPlane::getTraceCoefficient()
{
	return traceCoefficient;
}