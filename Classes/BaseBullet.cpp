#include "BaseBullet.h"
#include "AnimationUtil.h"
#include "ConfigUtil.h"

USING_NS_CC;

BaseBullet::BaseBullet()
{
}

bool BaseBullet::init()
{
	if (!BaseObject::init())
	{
		return false;
	}
	return true;
}

void BaseBullet::onDestroy()
{
	AnimationUtil::runParticleAnimation("Boom", this->getParent(), this);
	BaseObject::onDestroy();
}

void BaseBullet::onContact(Message& message)
{
	this->onDestroy();
}