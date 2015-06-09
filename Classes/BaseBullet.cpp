#include "BaseBullet.h"
#include "AnimationUtil.h"
#include "ConfigUtil.h"

USING_NS_CC;

BaseBullet::BaseBullet(int bulletParent) : _damage(100.0f), _bulletParent(bulletParent)
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
	AnimationUtil::runParticleAnimation("Boom.plist", this->getParent(), this);
	BaseObject::onDestroy();
}

void BaseBullet::onContact(BaseObject* contactNode)
{
	BaseObject::onContact(contactNode);
	if (_bulletParent != contactNode->getTag())
	{
		contactNode->reduceHP(_damage);
	}
	this->onDestroy();
}