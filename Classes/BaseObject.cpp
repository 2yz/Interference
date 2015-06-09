#include "BaseObject.h"

USING_NS_CC;

BaseObject::BaseObject() : _timer(0.0f)
{
}

BaseObject::~BaseObject()
{
}

bool BaseObject::init()
{
	if (!Node::init())
	{
		return false;
	}

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
	this->removeFromParentAndCleanup(true);
}

void BaseObject::onContact(BaseObject* contactNode)
{
	log("BaseObject::onContact(BaseObject* contactNode)");
}

void BaseObject::setParent(Node* parent)
{
	Node::setParent(parent);
	setTimeParent(dynamic_cast<TimeCoefficient*>(parent));
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

void BaseObject::update(float deltaTime)
{
	if (!_neverDie && _HP <= 0.0f)
		onDestroy();
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