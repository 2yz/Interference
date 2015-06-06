#include "BasePlane.h"

USING_NS_CC;


BasePlane::BasePlane(float radius) :BaseObject(), physicsRadius(radius), rotateVelocity(360.0f)
{
}

bool BasePlane::init()
{
	if (!BaseObject::init())
	{
		return false;
	}

	auto sprite1 = Sprite::create();
	auto sprite2 = Sprite::create();
	auto sprite3 = Sprite::create();
	auto sprite4 = Sprite::create();
	sprite2->setRotation(180.0f);
	sprite4->setRotation(180.0f);
	sprite3->setScale(0.2f);
	sprite4->setScale(0.2f);
	spriteVector.pushBack(sprite1);
	spriteVector.pushBack(sprite2);
	spriteVector.pushBack(sprite3);
	spriteVector.pushBack(sprite4);
	this->addChild(sprite1);
	this->addChild(sprite2);
	this->addChild(sprite3);
	this->addChild(sprite4);

	physicsBody->addShape(PhysicsShapeCircle::create(physicsRadius));

	this->scheduleUpdate();

	return true;
}

void BasePlane::update(float deltaTime)
{
	BaseObject::update(deltaTime);

	float spriteRotation = spriteVector.at(0)->getRotation() + rotateVelocity*deltaTime*timeCoefficient;
	if (spriteRotation > 360000.0f)
		spriteRotation -= 360000.0f;
	spriteVector.at(0)->setRotation(spriteRotation);
	spriteVector.at(1)->setRotation(180.0f - spriteRotation);
	spriteVector.at(2)->setRotation(spriteRotation * 2.0f);
	spriteVector.at(3)->setRotation(180.0f - spriteRotation * 2.0f);
}

// BasePlane* BasePlane::create()
// {
// 	BasePlane* pRet = new(std::nothrow) BasePlane(50.0f);
// 	CALL_INIT();
// }
