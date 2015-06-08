#include "BaseEnemy.h"

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
