#include "Attack.h"
#include "Bullet.h"

Attack::Attack()
{
	_CDTime = 0.08f;
	_skillCategory = ATTACK;
}

bool Attack::run(const cocos2d::Vec2& velocity, cocos2d::Node* parent, cocos2d::Node* target, int bulletParent)
{
	if (!Skill::run(velocity, parent, target, bulletParent))
	{
		return false;
	}
	auto bullet = Bullet::create(velocity, bulletParent);
	bullet->setPosition(target->getPosition());
	parent->addChild(bullet);

	for (int num = 1; num < 10; num++)
	{
		auto v2 = cocos2d::Vec2(velocity.y*sin(M_PI*num / 5) + velocity.x*cos(M_PI*num / 5), velocity.x*sin(M_PI*num / 5) + velocity.y*cos(M_PI*num / 5));
		auto bullet2 = Bullet::create(v2, bulletParent);
		bullet2->setPosition(target->getPosition());
		parent->addChild(bullet2);
	}
	// float random1 = cocos2d::random(7.0f, 13.0f);
	// auto v2 = cocos2d::Vec2(velocity.y*sin(M_PI / random1) + velocity.x*cos(M_PI / random1), velocity.x*sin(M_PI / random1) + velocity.y*cos(M_PI / random1));
	// auto bullet2 = Bullet::create(v2, bulletParent);
	// bullet2->setPosition(target->getPosition());
	// parent->addChild(bullet2);
	// // int random2 = cocos2d::random(5, 10);
	// auto v3 = cocos2d::Vec2(velocity.y*sin(-M_PI / random1) + velocity.x*cos(-M_PI / random1), velocity.x*sin(-M_PI / random1) + velocity.y*cos(-M_PI / random1));
	// auto bullet3 = Bullet::create(v3, bulletParent);
	// bullet3->setPosition(target->getPosition());
	// parent->addChild(bullet3);
	return true;
}