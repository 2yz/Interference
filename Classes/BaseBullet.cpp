#include "BaseBullet.h"

USING_NS_CC;

BaseBullet::BaseBullet()
{
}

bool BaseBullet::init()
{
	if (!BaseObject::init())
	{
		return false;
	}
	return true;
}