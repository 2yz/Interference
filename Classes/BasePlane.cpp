#include "BasePlane.h"

USING_NS_CC;


BasePlane::BasePlane(float radius) : shapeRadius(radius), rotateVelocity(360.0f)
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

	// normalShapeUp->setPosition(0.0f, 10.0f);
	// normalShapeDown->setPosition(0.0f, -10.0f);
	// smallShapeUp->setPosition(0.0f, 2.0f);
	// smallShapeDown->setPosition(0.0f, -2.0f);

	spriteVector.pushBack(sprite1);
	spriteVector.pushBack(sprite2);
	extraSpriteVector.pushBack(sprite3);
	extraSpriteVector.pushBack(sprite4);

	this->addChild(sprite1);
	this->addChild(sprite2);
	this->addChild(sprite3);
	this->addChild(sprite4);

	physicsBody->addShape(PhysicsShapeCircle::create(shapeRadius));

	this->scheduleUpdate();

	return true;
}

void BasePlane::onEnter()
{
	BaseObject::onEnter();
	// TODO check action
	// auto rotateBy = RepeatForever::create(RotateBy::create(0.5f, 360.0f));
	// auto tintTo = TintTo::create(2.0f, random(0.0f, 255.0f), random(0.0f, 255.0f), random(0.0f, 255.0f));
	// auto spwan = Spawn::createWithTwoActions(rotateBy, tintTo);
	// for (auto sprite : spriteVector)
	// {
	// 	// Blend has been set in base class
	// 	sprite->runAction(rotateBy->clone());
	// 	sprite->runAction(TintTo::create(2.0f, random(0.0f, 255.0f), random(0.0f, 255.0f), random(0.0f, 255.0f)));
	// }
	for (auto extraSprite : extraSpriteVector)
	{
		extraSprite->setBlendFunc(BlendFunc::ADDITIVE);
		// extraSprite->runAction(rotateBy->clone());
		// extraSprite->runAction(TintTo::create(2.0f, random(0.0f, 255.0f), random(0.0f, 255.0f), random(0.0f, 255.0f)));
	}
}

void BasePlane::update(float deltaTime)
{
	BaseObject::update(deltaTime);

	if (spriteVector.at(0) == nullptr || spriteVector.at(1) == nullptr || extraSpriteVector.at(0) == nullptr || extraSpriteVector.at(1) == nullptr)
		return;
	float spriteRotation = spriteVector.at(0)->getRotation() + rotateVelocity*deltaTime*timeCoefficient;
	if (spriteRotation > 360000.0f)
		spriteRotation -= 360000.0f;
	spriteVector.at(0)->setRotation(spriteRotation);
	spriteVector.at(1)->setRotation(180.0f - spriteRotation);
	extraSpriteVector.at(0)->setRotation(spriteRotation * 2.0f);
	extraSpriteVector.at(1)->setRotation(180.0f - spriteRotation * 2.0f);
}

// BasePlane* BasePlane::create()
// {
// 	BasePlane* pRet = new(std::nothrow) BasePlane(50.0f);
// 	CALL_INIT();
// }
