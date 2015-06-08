#ifndef BASEOBJECT_H_
#define BASEOBJECT_H_

#include "cocos2d.h"
#include "TimeCoefficient.h"

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

class BaseObject : public cocos2d::Node, public TimeCoefficient
{
public:
	BaseObject();
	virtual bool init() override;
	virtual void onEnter() override;
	virtual void onDestroy();
	virtual void onContact(BaseObject* contactNode);
	virtual void setParent(Node* parent) override;
	void reduceHP(float reduceValue);
	void setVelocity(const cocos2d::Vect& velocity);
protected:
	cocos2d::PhysicsBody* _physicsBody;
	cocos2d::Vector<cocos2d::Sprite*> _spriteVector;
	float _HP;
	bool _neverDie; // Is never under attack
	float _velocityMagnitudeMax;
	float _accelerationMagnitude;
	virtual void update(float deltaTime) override;
	float getVelocityMagnitude();
	float getVelocityDirection();
};

#endif /* BASEOBJECT_H_ */