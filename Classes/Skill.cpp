#include "Skill.h"

Skill::Skill() : timer_(0.0f), cd_(false)
{
}

Skill::~Skill()
{
}

bool Skill::init()
{
	if (!Node::init())
	{
		return false;
	}
	this->scheduleUpdate();
	return true;
}

bool Skill::cast(cocos2d::Layer* battle_layer, BaseObject* skill_parent, const cocos2d::Vec2& direction, BaseObject* skill_targer)
{
	if (battle_layer == nullptr)
		return false;
    
	if (cd_)
		return false;
	cd_ = true;
	return true;
}

SkillCategory Skill::getSkillCategory()
{
	return skill_category_;
}

void Skill::update(float deltaTime)
{
	Node::update(deltaTime);
	if (cd_)
	{
		timer_ += deltaTime;
		if (timer_ >= cd_time_)
		{
			cd_ = false;
			timer_ = 0.0f;
		}
	}
}