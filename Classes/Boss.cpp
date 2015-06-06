#include "Boss.h"

Boss::Boss()
{
}

bool Boss::init()
{
	if (!BasePlane::init())
	{
		return false;
	}
	return true;
}