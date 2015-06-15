#include "Attack.h"
#include "Bullet.h"
#include "SimpleAudioEngine.h"
#include "AudioEngine.h"

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
    //CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("hoot.mp3",false,1.5f);
    cocos2d::experimental::AudioEngine::play2d("Shoot.mp3",false,0.3f);
	return true;
}