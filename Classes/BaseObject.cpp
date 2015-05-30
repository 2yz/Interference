#include "BaseObject.h"

USING_NS_CC;

BaseObject::BaseObject()
{
	physicsBody = PhysicsBody::create();
	log("BaseObject()");
}

BaseObject::BaseObject(float radius)
{
	physicsBody = PhysicsBody::createCircle(radius);
	log("BaseObject(float radius)");
}

BaseObject::BaseObject(cocos2d::Size& size)
{
	physicsBody = PhysicsBody::createBox(size);
}

bool BaseObject::init()
{
	if (!Node::init())
	{
		return false;
	}
	physicsBody->setRotationEnable(false);
	physicsBody->setGravityEnable(false);
	this->setPhysicsBody(physicsBody);
	return true;
}