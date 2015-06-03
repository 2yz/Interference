#include "BaseBullet.h"

USING_NS_CC;

BaseBullet::BaseBullet(cocos2d::Size size) : BaseObject(size)
{
	physicsBody->setGroup(-1);
	physicsBody->setContactTestBitmask(0x0000FFFF);
	physicsBody->setVelocityLimit(800.0f);
}

bool BaseBullet::init()
{
	if (!BaseObject::init())
	{
		return false;
	}
	bullet = Sprite::create();
	this->addChild(bullet);
	return true;
}

void BaseBullet::onEnter()
{
	BlendFunc blend = { GL_SRC_ALPHA, GL_ONE };
	bullet->setBlendFunc(blend);
}