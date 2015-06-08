#include "Enemy.h"

Enemy::Enemy()
{
}

bool Enemy::init()
{
	if (!BasePlane::init())
	{
		return false;
	}
	return true;
}
