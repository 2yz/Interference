#include "PlayerUserData.h"

PlayerUserData::PlayerUserData(float hp, float hp_max) : hp_(hp), hp_max_(hp_max)
{
}

float PlayerUserData::getHP()
{
	return hp_;
}

void PlayerUserData::setHP(float hp)
{
	hp_ = hp;
}

float PlayerUserData::getMaxHP()
{
	return hp_max_;
}

void PlayerUserData::setMaxHP(float hp_max)
{
	hp_max_ = hp_max;
}

bool PlayerUserData::isAlive()
{
	if (hp_ > 0.0f)
		return true;
	else
		return false;
}