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

void BaseEnemy::onContact(Message& message)
{
	if (message.getInt("Tag") == PLAYER_TAG && _beDestroyable)
		this->onDestroy();
	if (message.getInt("Tag") == PLAYER_BULLET_TAG)
		_HP -= message.getFloat("Damage");
}