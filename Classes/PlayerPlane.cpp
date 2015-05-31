#include "PlayerPlane.h"
#include "Controller.h"

USING_NS_CC;

PlayerPlane::PlayerPlane() 
{
	log("PlayerPlane()");
	
}

// bool PlayerPlane::init()
// {
// 	if (!BasePlayer::init())
// 	{
// 		return false;
// 	}
// 	return true;
// }

// PlayerPlane* PlayerPlane::create()
// {
// 	PlayerPlane* pRet = new(std::nothrow) PlayerPlane();
// 	CALL_INIT();
// }

// void PlayerPlane::update(float deltaTime)
// {
// 	// log("LinearDamping: %f", physicsBody->getLinearDamping());
// 	// log("PlayerPlane X: %f Y: %f", this->getPositionX(), this->getPositionY());
// 	
// }