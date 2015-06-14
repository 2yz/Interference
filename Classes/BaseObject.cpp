#include "BaseObject.h"

USING_NS_CC;

BaseObject::BaseObject() : _timer(0.0f)
{
}

BaseObject::~BaseObject()
{
	_spriteVector.clear();
}

bool BaseObject::init()
{
	if (!Node::init())
	{
		return false;
	}
	// Initial Message
	initMessage();

	// Create Physics Body
	_physicsBody = PhysicsBody::create();
	_physicsBody->setRotationEnable(false);
	this->setPhysicsBody(_physicsBody);

	this->scheduleUpdate();

	return true;
}

void BaseObject::onEnter()
{
	Node::onEnter();
	for (auto sprite : _spriteVector)
	{
		sprite->setBlendFunc(BlendFunc::ADDITIVE);
	}
	this->setCameraMask(1 << 1);
}

void BaseObject::onDestroy()
{
	this->unscheduleUpdate();
	this->removeFromParentAndCleanup(true);
}

void BaseObject::onContact(Message& message)
{
	log("BaseObject::onContact(Message& message)");
}

void BaseObject::initMessage()
{
}

Message BaseObject::getMessage()
{
	return _message;
}

void BaseObject::setParent(Node* parent)
{
	Node::setParent(parent);
	setTimeParent(dynamic_cast<TimeCoefficient*>(parent));
}

void BaseObject::setVelocity(const cocos2d::Vect& velocity)
{
	this->getPhysicsBody()->setVelocity(velocity);
}

float BaseObject::getVelocityMagnitude()
{
	return _physicsBody->getVelocity().length();
}

// TODO getVelocityDirection
float BaseObject::getVelocityDirection()
{
	return 0.0f;
}

void BaseObject::update(float deltaTime)
{
	if (!_neverDie && _HP <= 0.0f)
		this->onDestroy();
}