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

bool BaseEnemy::onContact(BaseObject* contactNode)
{
	if (contactNode->getTag() == PLAYER_TAG)
	{
		contactNode->reduceHP(_destroyDamage);
		this->onDestroy();
		return true;
	}
	return false;
}