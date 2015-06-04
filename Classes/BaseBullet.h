#ifndef BASEBULLET_H_
#define BASEBULLET_H_

#include "cocos2d.h"

#define CALL_INIT() \
if (pRet && pRet->init()) \
{ \
	pRet->autorelease(); \
	return pRet; \
} \
else \
{ \
	delete pRet; \
	pRet = NULL; \
	return NULL; \
} 

class BaseBullet : public cocos2d::Sprite
{
public:
	BaseBullet();
	// BaseBullet(float radius);
	// BaseBullet(cocos2d::Size& size);
	virtual bool init() override;
	virtual bool initWithSpriteFrameName(const std::string& spriteFrameName) override;
protected:
	cocos2d::PhysicsBody* physicsBody;
	virtual void onEnter() override;
};

#endif /* BASEBULLET_H_ */