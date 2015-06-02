#ifndef __AnimationUtil_H__
#define __AnimationUtil_H__

#include "cocos2d.h"
USING_NS_CC;

class AnimationUtil
{
public:

    static Animation* createWithSingleFrameName(const char* name, float delay, int iLoops);

    static Animation* createWithFrameNameAndNum(const char* name, int iNum, float delay, int iLoops);
    
    static Animation* createWithSingleSpriteNameAndNum(const char* name, int iNum, float delay, int iLoops);
};

#endif