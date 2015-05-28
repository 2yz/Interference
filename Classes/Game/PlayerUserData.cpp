#include "PlayerUserData.h"

PlayerUserData::PlayerUserData(int initHP) : HP(initHP)
{
}

bool PlayerUserData::isAliveUnderAttack(int damage)
{
	HP -= damage;
	if (HP <= 0)
		return false;
	else
		return true;
}

int PlayerUserData::getHP() const
{
	return HP;
}