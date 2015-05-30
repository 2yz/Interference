#include "PlayerPlane.h"
#include "Controller.h"

USING_NS_CC;

PlayerPlane::PlayerPlane() : initHP(1000), acceleration(500.0f), maxSpeed(500.0f)
{
	log("PlayerPlane()");
	physicsBody->setContactTestBitmask(0xFFFFFFFF);
	physicsBody->setLinearDamping(1.0f);
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

PlayerPlane* PlayerPlane::create()
{
	PlayerPlane* pRet = new(std::nothrow) PlayerPlane();
	CALL_INIT();
}

void PlayerPlane::update(float delta)
{
	log("LinearDamping: %f", physicsBody->getLinearDamping());
	if ((Controller::getMoveUp() ^ Controller::getMoveDown()) && (Controller::getMoveLeft() ^ Controller::getMoveRight()))
	{
		physicsBody->setVelocity(physicsBody->getVelocity() + acceleration * delta *
			Vec2(static_cast<float>(Controller::getMoveRight() - Controller::getMoveLeft()) / static_cast<float>(sqrt(2.0)),
			static_cast<float>(Controller::getMoveUp() - Controller::getMoveDown()) / static_cast<float>(sqrt(2.0))));
	}
	else if (Controller::getMoveUp() || Controller::getMoveDown() || Controller::getMoveLeft() || Controller::getMoveRight())
	{
		physicsBody->setVelocity(physicsBody->getVelocity() + acceleration * delta *
			Vec2(static_cast<float>(Controller::getMoveRight() - Controller::getMoveLeft()),
			static_cast<float>(Controller::getMoveUp() - Controller::getMoveDown())));
	}
}