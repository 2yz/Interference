#ifndef BASEOBJECT_H_
#define BASEOBJECT_H_

#include "cocos2d.h"
#include "TimeCoefficient.h"
#include "Message.h"

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
#include "Message.h"

class BaseObject : public cocos2d::Node, public TimeCoefficient
{
public:
	BaseObject();
	virtual ~BaseObject();
	virtual bool init() override;
	virtual void onEnter() override;
	virtual void onDestroy();
	virtual void onContact(Message& message);
	virtual void initMessage();
	virtual Message getMessage();
	virtual void setParent(Node* parent) override;
	void setVelocity(const cocos2d::Vect& velocity);
	float getVelocityMagnitude();
	float getVelocityDirection();
	virtual void update(float deltaTime) override;
protected:
	Message _message;
	float _timer;
	float _HP;
	bool _neverDie; // Is never under attack
	float _velocityMagnitude; // Velocity unit is pixel per second
	float _velocityDirection; // Velocity direction angle in radian measure
	cocos2d::PhysicsBody* _physicsBody;
	cocos2d::Vector<cocos2d::Sprite*> _spriteVector;
};

#endif /* BASEOBJECT_H_ */