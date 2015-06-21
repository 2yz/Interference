#ifndef __AnimationUtil_H__
#define __AnimationUtil_H__

#include "cocos2d.h"
USING_NS_CC;

class AnimationUtil
{
public:
    
	// Create Animation With Different Method
	static Animation* createWithSingleFrameName(const char* name, float delay, int loops);
	static Animation* createWithFrameNameAndNum(const char* name, int num, float delay, int loops);
	static Animation* createWithSingleSpriteNameAndNum(const char* name, int num, float delay, int loops);

	// Run Picture Or Particle Animation
	static bool runPictureAnimation(const char* name, Node* parent, Node* target);
    static ParticleSystemQuad* runParticleAnimation(const std::string& name, Node* parent, Node* target, bool remove_on_finish = true);
};

#endif


