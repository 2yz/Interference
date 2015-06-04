#include "BaseObject.h"

USING_NS_CC;

BaseObject::BaseObject() : timeCoefficient(1.0f)
{
	physicsBody = PhysicsBody::create();
	blend = { GL_SRC_ALPHA, GL_ONE };
}

// BaseObject::BaseObject(float radius)
// {
// 	physicsBody = PhysicsBody::createCircle(radius);
// 	log("BaseObject(float radius)");
// }
// 
// BaseObject::BaseObject(cocos2d::Size& size)
// {
// 	physicsBody = PhysicsBody::createBox(size);
// }

bool BaseObject::init()
{
	if (!Node::init())
	{
		return false;
	}
	physicsBody->setRotationEnable(false);
	this->setPhysicsBody(physicsBody);
	this->scheduleUpdate();
	return true;
}

void BaseObject::onEnter()
{
	Node::onEnter();
	for (auto sprite : spriteVector)
	{
		sprite->setBlendFunc(blend);
	}
}

void BaseObject::onContact(cocos2d::Node* contactNode)
{
}

void BaseObject::setVelocity(const cocos2d::Vect& velocity)
{
	this->getPhysicsBody()->setVelocity(velocity);
}

void BaseObject::setTimeCoefficient(float coefficient)
{
	this->timeCoefficient = coefficient;
}

float BaseObject::getVelocityMagnitude()
{
	return physicsBody->getVelocity().length();
}

// TODO getVelocityDirection
float BaseObject::getVelocityDirection()
{
	return 0.0f;
}

// void BaseObject::update(float deltaTime)
// {
// 	log("BaseObject::update(float deltaTime)");
// }