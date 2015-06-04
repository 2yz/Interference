#include "BaseBullet.h"
#include "ConfigUtil.h"
USING_NS_CC;


BaseBullet::BaseBullet()
{
}

bool BaseBullet::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	// this->setTag(-2);
	// bullet = Sprite::create();
	// this->addChild(bullet);
	return true;
	// physicsBody = PhysicsBody::create();
	// return BaseBullet::initWithSpriteFrameName("");
}

bool BaseBullet::initWithSpriteFrameName(const std::string& spriteFrameName)
{
	if (!Sprite::initWithSpriteFrameName(spriteFrameName))
	{
		return false;
	}
	return true;
}

void BaseBullet::onEnter()
{
	Sprite::onEnter();
	BlendFunc blend = { GL_SRC_ALPHA, GL_ONE };
	this->setBlendFunc(blend);
}