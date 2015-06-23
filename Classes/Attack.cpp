#include "Attack.h"
#include "Bullet.h"
#include "ConfigUtil.h"
#include "AudioEngine.h"

Attack::Attack()
{
	cd_time_ = 0.15f;
	skill_category_ = ATTACK;
}

void Attack::onEnter()
{
	Skill::onEnter();
	switch (getParent()->getTag())
	{
	case kPlayerTag:
		skill_parent_ = kPlayerTag;
		break;
	case kEnemyTag:
		skill_parent_ = kEnemyTag;
		break;
	default:
		skill_parent_ = 0;
		break;
	}
}

bool Attack::cast(cocos2d::Layer* battle_manager, BaseObject* skill_parent, const cocos2d::Vec2& direction, BaseObject* skill_targer)
{
	if (!Skill::cast(battle_manager, skill_parent, direction, skill_targer))
		return false;
	if (skill_parent_ == 0)
		return false;
	auto bullet = Bullet::create(skill_parent_, direction);
	bullet->setPosition(skill_parent->getPosition());
	battle_manager->addChild(bullet);
	cocos2d::experimental::AudioEngine::play2d(ATTACK_AUDIO, false, ATTACK_VOLUME);
	return true;
}
