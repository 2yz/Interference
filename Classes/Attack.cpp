#include "Attack.h"
#include "Bullet.h"
#include "SimpleAudioEngine.h"

Attack::Attack()
{
	_skillCategory = ATTACK;
	_CDTime = 0.08f;
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
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("bullet.mp3",false,1.5f);
	return true;
}