#include "AnimationUtil.h"

Animation* AnimationUtil::createWithSingleFrameName(const char* name, float delay, int iLoops)
{
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	Vector<SpriteFrame*> frameVec;
	SpriteFrame* frame = NULL;
	int index = 1;
	do {
		frame = cache->getSpriteFrameByName(StringUtils::format("%s%d.png", name, index++));
		if (frame == NULL)
		{
			break;
		}
		frameVec.pushBack(frame);
	} while (true);
	Animation* animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(iLoops);
	animation->setRestoreOriginalFrame(true);
	animation->setDelayPerUnit(delay);
	return animation;
}

Animation* AnimationUtil::createWithFrameNameAndNum(const char* name, int iNum, float delay, int iLoops)
{
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	Vector<SpriteFrame*> frameVec;;
	SpriteFrame* frame = NULL;
	for (int i = 1; i <= iNum; i++)
	{
		frame = cache->getSpriteFrameByName(StringUtils::format("%s%d.png", name, i));
		if (frame == NULL)
		{
			break;
		}
		frameVec.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(iLoops);
	animation->setRestoreOriginalFrame(true);
	animation->setDelayPerUnit(delay);
	return animation;
}

Animation* AnimationUtil::createWithSingleSpriteNameAndNum(const char* name, int iNum, float delay, int iLoops)
{
	auto animation = Animation::create();
	for (int i = 1; i < iNum; i++)
	{
		char szName[500] = { 0 };
		sprintf(szName, "%s%d.png", name, i);
		animation->addSpriteFrameWithFile(szName);
	}
	animation->setLoops(iLoops);
	animation->setRestoreOriginalFrame(true);
	animation->setDelayPerUnit(delay);
	return animation;
}

bool AnimationUtil::runPictureAnimation(const char* name, Node* parent, Node* target)
{
	if (parent == nullptr || target == nullptr)
	{
		return false;
	}
	Sprite* animation = Sprite::create();
	animation->setPosition(target->getPosition());
	parent->addChild(animation);
	animation->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(name)));
	return true;
}

ParticleSystemQuad* AnimationUtil::runParticleAnimation(const char* name, Node* parent, Node* target, bool removeOnFinish)
{
	if (parent == nullptr || target == nullptr)
	{
		return nullptr;
	}
	auto particle = ParticleSystemQuad::create(name);
	particle->setPosition(target->getPosition());
	particle->setAutoRemoveOnFinish(removeOnFinish);
	parent->addChild(particle);
	return particle;
}
