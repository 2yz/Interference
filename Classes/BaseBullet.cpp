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
	AnimationUtil::runParticleAnimation(BOOM_PARTICLE, this->getParent(), this);
	cocos2d::experimental::AudioEngine::play2d(IMPACT_AUDIO, false, IMPACT_VOLUME);
	BaseObject::onDestroy();
}

void BaseBullet::onContact(Message& message)
{
	this->onDestroy();
}