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

// enum BaseShape
// {
// 	CIRCLE,
// 	BOX,
// 	NOSHAPE
// };

class BaseObject : public cocos2d::Node
{
public:
	BaseObject();
	// explicit BaseObject(float radius);
	// explicit BaseObject(cocos2d::Size& size);
	virtual bool init() override;
	virtual void onEnter() override;
	virtual void onContact(cocos2d::Node* contactNode);
	void setVelocity(const cocos2d::Vect& velocity);
	void setTimeCoefficient(float coefficient);
protected:
	// BaseShape baseShape;
	// float radius;
	// cocos2d::Size size;
	cocos2d::PhysicsBody* physicsBody;
	cocos2d::Vector<cocos2d::Sprite*> spriteVector;
	cocos2d::BlendFunc blend;
	float velocityMagnitudeMax;
	float accelerationMagnitude;
	float timeCoefficient;
	float getVelocityMagnitude();
	float getVelocityDirection();
	// virtual void update(float deltaTime) override;
};

#endif /* BASEOBJECT_H_ */