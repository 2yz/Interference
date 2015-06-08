#include "Boss.h"

Boss::Boss()
{
}

bool Boss::init()
{
	if (!BaseEnemy::init())
	{
		return false;
	}
	return true;
}