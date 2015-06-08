#include "BasePlane.h"
#include "ConfigUtil.h"

USING_NS_CC;

BasePlane::BasePlane(float radius) :BaseObject(), physicsRadius(radius), rotateVelocity(180.0f)
{
}

BasePlane::~BasePlane()
{
}

bool BasePlane::init()
{
	if (!BaseObject::init())
	{
		return false;
	}

	physicsBody->addShape(PhysicsShapeCircle::create(physicsRadius, MATERIAL_PLANE));

	this->scheduleUpdate();

	return true;
}

void BasePlane::runSkill(const cocos2d::Vec2& velocity, SkillCategory skillCategory, int skillIndex)
{
}

void BasePlane::update(float deltaTime)
{
	BaseObject::update(deltaTime);
}
