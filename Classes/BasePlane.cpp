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
    TailFire = ParticleSystemQuad::create("Tail.plist");
    

	normalShapeDown->setRotation(180.0f);
	smallShapeDown->setRotation(180.0f);
    TailFire->setAngle(0.0f);
    //TailFire->set(360.0f);
    TailFire->cocos2d::ParticleSystem::setTotalParticles(0.0f);
    TailFire->cocos2d::ParticleSystem::setAngleVar(180.0f);

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
    this->addChild(TailFire);

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

	auto tintTo1 = TintTo::create(2.0f, random(0.0f, 255.0f), random(0.0f, 255.0f), random(0.0f, 255.0f));
	auto tintTo2 = TintTo::create(2.0f, random(0.0f, 255.0f), random(0.0f, 255.0f), random(0.0f, 255.0f));
	auto tintTo3 = TintTo::create(2.0f, random(0.0f, 255.0f), random(0.0f, 255.0f), random(0.0f, 255.0f));
	auto tintTo4 = TintTo::create(2.0f, random(0.0f, 255.0f), random(0.0f, 255.0f), random(0.0f, 255.0f));
	normalShapeUp->runAction(tintTo1);
	normalShapeDown->runAction(tintTo2);
	smallShapeUp->runAction(tintTo3);
	smallShapeDown->runAction(tintTo4);

}

// BasePlane* BasePlane::create()
// {
// 	BasePlane* pRet = new(std::nothrow) BasePlane(50.0f);
// 	CALL_INIT();
// }
