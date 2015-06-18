#include "BaseBullet.h"
#include "AnimationUtil.h"
#include "ConfigUtil.h"
#include "AudioEngine.h"

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
	cocos2d::experimental::AudioEngine::play2d(kImpactAudio, false, kImpactVolume);
	BaseObject::onDestroy();
}

void BaseBullet::onContact(Message& message)
{
	this->onDestroy();
}