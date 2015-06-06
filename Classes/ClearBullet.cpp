#include "ClearBullet.h"

ClearBullet::ClearBullet()
{
}

bool ClearBullet::init()
{
	if (!BaseObject::init())
	{
		return false;
	}
	return true;
}