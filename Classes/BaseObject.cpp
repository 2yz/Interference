#include "BaseObject.h"
#include "ConfigUtil.h"

USING_NS_CC;

BaseObject::BaseObject() : timer_(0.0f)
{
}

BaseObject::~BaseObject()
{
	sprite_vector_.clear();
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
	physics_body_ = PhysicsBody::create();
	physics_body_->setRotationEnable(false);
	this->setPhysicsBody(physics_body_);

	this->scheduleUpdate();
	
	return true;
}

void BaseObject::onEnter()
{
	Node::onEnter();
	for (auto sprite : sprite_vector_)
	{
		sprite->setBlendFunc(BlendFunc::ADDITIVE);
	}
	this->setCameraMask(1 << 1);
}

void BaseObject::onDestroy()
{
	this->removeFromParentAndCleanup(true);
}

void BaseObject::onContact(Message& message)
{
}

void BaseObject::initMessage()
{
}

Message BaseObject::getMessage()
{
	return message_;
}

void BaseObject::setParent(Node* parent)
{
	Node::setParent(parent);
	setTimeParent(dynamic_cast<TimeCoefficient*>(parent));
}

void BaseObject::setVelocity(const cocos2d::Vect& velocity)
{
	if (physics_body_)
		physics_body_->setVelocity(velocity);
}

float BaseObject::getVelocityMagnitude()
{
	return physics_body_->getVelocity().length();
}

// TODO getVelocityDirection
float BaseObject::getVelocityDirection()
{
	return 0.0f;
}
