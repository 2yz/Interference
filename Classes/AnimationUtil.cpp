#include "AnimationUtil.h"

Animation* AnimationUtil::createWithSingleFrameName(const char* name, float delay, int iLoops)
{
    SpriteFrameCache* cache = SpriteFrameCache::getInstance();
    
    Vector<SpriteFrame*> frameVec;
    SpriteFrame* frame = NULL;
    int index = 1;
    do {
        frame = cache->getSpriteFrameByName(StringUtils::format("%s%d.png", name,index++));
        
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
        char szName[500] = {0};
        sprintf(szName, "%s%d.png", name, i);
        animation->addSpriteFrameWithFile(szName);
    }
    animation->setLoops(iLoops);
    animation->setRestoreOriginalFrame(true);
    animation->setDelayPerUnit(delay);
    return animation;
}

//Demo
/*
Sprite* runSp = Sprite::create("run1.png");
runSp->setPosition(Point(200, 200));
this->addChild(runSp);

SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
frameCache->addSpriteFramesWithFile("boys.plist", "boys.png");

Animation* animation = AnimationUtil::createWithSingleFrameName("run", 0.1f, -1);
//Animation* animation = AnimationUtil::createWithFrameNameAndNum("run", 15, 0.1f, -1);
//Animation* animation = AnimationUtil::createWithSingleSpriteNameAndNum("Shockwave", 100, 0.05f, -1);

runSp->runAction(Animate::create(animation));
*/
