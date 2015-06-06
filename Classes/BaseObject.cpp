#include "BaseObject.h"

USING_NS_CC;

BaseObject::BaseObject() : timeCoefficient(1.0f)
{	
}

bool BaseObject::init()
{
	if (!Node::init())
	{
		return false;
	}

	// Create Physics Body
	physicsBody = PhysicsBody::create();
	physicsBody->setRotationEnable(false);
	this->setPhysicsBody(physicsBody);

	return true;
}

void BaseObject::onEnter()
{
	Node::onEnter();
	for (auto sprite : spriteVector)
	{
		sprite->setBlendFunc(BlendFunc::ADDITIVE);
	}
}

void BaseObject::onDestory()
{
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