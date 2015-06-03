#include "BaseBullet.h"
#include "ConfigUtil.h"
USING_NS_CC;

BaseBullet::BaseBullet(cocos2d::Size size) : BaseObject(size)
{
	physicsBody->setGroup(-1);
	physicsBody->setContactTestBitmask(BULLET_CONTACT_MASK);
	physicsBody->setCollisionBitmask(BULLET_COLLISION_MASK);
	physicsBody->setCategoryBitmask(BULLET_CATEGORY_MASK);
	physicsBody->setVelocityLimit(800.0f);
}

bool BaseBullet::init()
{
	if (!BaseObject::init())
	{
		return false;
	}
	this->setTag(-2);
	bullet = Sprite::create();
	this->addChild(bullet);
	return true;
}

void BaseBullet::onEnter()
{
	BlendFunc blend = { GL_SRC_ALPHA, GL_ONE };
	bullet->setBlendFunc(blend);
}