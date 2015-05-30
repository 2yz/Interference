#include "PlayerPlane.h"

USING_NS_CC;

PlayerPlane::PlayerPlane()
{
	log("PlayerPlane()");
}

PlayerPlane* PlayerPlane::create()
{
	PlayerPlane* pRet = new(std::nothrow) PlayerPlane();
	CALL_INIT();
}