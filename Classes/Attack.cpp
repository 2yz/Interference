#include "Attack.h"
#include "Bullet.h"

Attack::Attack()
{
	_skillCategory = ATTACK;
	_CDTime = 0.04f;
}

bool Attack::run(const cocos2d::Vec2& velocity, cocos2d::Node* parent, cocos2d::Node* target, int bulletParent)
{
	if (!Skill::run(velocity, parent, target,bulletParent))
	{
		return false;
	}
	auto bullet = Bullet::create(velocity,bulletParent);
	bullet->setPosition(target->getPosition());
	parent->addChild(bullet);
	return true;
}