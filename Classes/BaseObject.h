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
	explicit BaseObject(float radius);
	explicit BaseObject(cocos2d::Size& size);
	virtual bool init() override;
protected:
	// BaseShape baseShape;
	// float radius;
	// cocos2d::Size size;
	cocos2d::PhysicsBody* physicsBody;
	float timer;
};

#endif /* BASEOBJECT_H_ */