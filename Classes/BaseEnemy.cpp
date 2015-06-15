#include "BaseEnemy.h"
#include "ConfigUtil.h"

BaseEnemy::BaseEnemy()
{
}

bool BaseEnemy::init()
{
	if (!BasePlane::init())
	{
		return false;
	}
	return true;
}
