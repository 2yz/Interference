#include "BasePlane.h"

USING_NS_CC;

BasePlane::BasePlane() : BasePlane(50.0f)
{
	log("BasePlane()");
}

BasePlane::BasePlane(float radius) : BaseObject(radius)
{
	log("BasePlane(float radius)");
}

bool BasePlane::init()
{
	if (!BaseObject::init())
	{
		return false;
	}

	normalShapeUp = Sprite::create();
	normalShapeDown = Sprite::create();
	smallShapeUp = Sprite::create();
	smallShapeDown = Sprite::create();

	// normalShapeDown->setRotation(180.0f);
	// smallShapeDown->setRotation(180.0f);

	smallShapeUp->setScale(0.2f);
	smallShapeDown->setScale(0.2f);

	// normalShapeUp->setPosition(0.0f, 10.0f);
	// normalShapeDown->setPosition(0.0f, -10.0f);
	// smallShapeUp->setPosition(0.0f, 2.0f);
	// smallShapeDown->setPosition(0.0f, -2.0f);

	this->addChild(normalShapeUp);
	this->addChild(normalShapeDown);
	this->addChild(smallShapeUp);
	this->addChild(smallShapeDown);

	return true;
}

void BasePlane::onEnter()
{
	BaseObject::onEnter();
	BlendFunc blend = { GL_SRC_ALPHA, GL_ONE };
	normalShapeUp->setBlendFunc(blend);
	normalShapeDown->setBlendFunc(blend);
	smallShapeUp->setBlendFunc(blend);
	smallShapeDown->setBlendFunc(blend);
}

// BasePlane* BasePlane::create()
// {
// 	BasePlane* pRet = new(std::nothrow) BasePlane(50.0f);
// 	CALL_INIT();
// }
