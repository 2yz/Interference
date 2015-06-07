#include "BaseObject.h"

USING_NS_CC;

BaseObject::BaseObject() : _HP(1000.0f), _neverDie(false), timeCoefficient(1.0f)
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
		sprite->setColor(Color3B(255, 0, 0));

	}
}

void BaseObject::onDestory()
{
}

void BaseObject::onContact(BaseObject* contactNode)
{
	log("BaseObject::onContact(BaseObject* contactNode)");
}

void BaseObject::reduceHP(float reduceValue)
{
	if (!_neverDie)
		_HP -= reduceValue;
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