#ifndef BASEOBJECT_H_
#define BASEOBJECT_H_

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

class BaseObject : public cocos2d::Node
{
public:
	BaseObject();
	virtual bool init() override;
	virtual void onEnter() override;
	virtual void onDestory();
	virtual void onContact(cocos2d::Node* contactNode);
	void setVelocity(const cocos2d::Vect& velocity);
	void setTimeCoefficient(float coefficient);
protected:
	cocos2d::PhysicsBody* physicsBody;
	cocos2d::Vector<cocos2d::Sprite*> spriteVector;
	int _HP;
	float velocityMagnitudeMax;
	float accelerationMagnitude;
	float timeCoefficient;
	float getVelocityMagnitude();
	float getVelocityDirection();
};

#endif /* BASEOBJECT_H_ */