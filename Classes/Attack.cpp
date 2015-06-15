#include "Attack.h"
#include "Bullet.h"
#include "ConfigUtil.h"

Attack::Attack()
{
	cd_time_ = 0.08f;
	skill_category_ = ATTACK;
}

void Attack::onEnter()
{
	Skill::onEnter();
	switch (getParent()->getTag())
	{
	case PLAYER_TAG:
		skill_parent_ = PLAYER;
		break;
	case ENEMY_TAG:
		skill_parent_ = ENEMY;
		break;
	default:
		skill_parent_ = 0;
		break;
	}
}

bool Attack::cast(cocos2d::Layer* battle_layer, BaseObject* skill_parent, const cocos2d::Vec2& direction, BaseObject* skill_targer)
{
	if (!Skill::cast(battle_layer,skill_parent,direction,skill_targer))
		return false;
	if (skill_parent_ == 0)
		return false;
	auto bullet = Bullet::create(skill_parent_, direction);
	bullet->setPosition(skill_parent->getPosition());
	battle_layer->addChild(bullet);
	return true;
}
