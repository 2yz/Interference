#include "BasePlane.h"
#include "ConfigUtil.h"

USING_NS_CC;

BasePlane::BasePlane(float radius) :BaseObject(), _physicsRadius(radius), _rotateVelocity(180.0f)
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
