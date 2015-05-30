#include "BasePlane.h"

USING_NS_CC;

BasePlane::BasePlane() : BasePlane(50.0f)
{
	log("BasePlane()");
}

BasePlane::BasePlane(float radius) : BaseObject(radius)
{
	log("BasePlane(float radius)");
}

bool BasePlane::init()
{
	if (!BaseObject::init())
	{
		return false;
	}
	plane = Sprite::createWithSpriteFrameName("myPlane.png");
	this->addChild(plane);
	return true;
}

BasePlane* BasePlane::create()
{
	BasePlane* pRet = new(std::nothrow) BasePlane(50.0f);
	CALL_INIT();
}
