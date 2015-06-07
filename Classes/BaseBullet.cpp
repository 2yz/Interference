#include "BaseBullet.h"
#include "AnimationUtil.h"
#include "ConfigUtil.h"

USING_NS_CC;

BaseBullet::BaseBullet(int bulletParent) : _bulletParent(bulletParent)
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

void BaseBullet::onDestory()
{
	BaseObject::onDestory();
	AnimationUtil::runParticleAnimation("Boom.plist", this->getParent(), this);
	this->removeFromParentAndCleanup(true);
}

void BaseBullet::onContact(BaseObject* contactNode)
{
	BaseObject::onContact(contactNode);
	if (_bulletParent != contactNode->getTag())
	{
		contactNode->reduceHP(_damage);
	}
	this->onDestory();
}