#include "Skill.h"
#include "SkillUserData.h"
#include "ConfigUtil.h"

USING_NS_CC;

Skill::Skill() : timer_(0.0f), cd_(false), cd_time_coefficient_(1.0f)
{
}

Skill::~Skill()
{
	CC_SAFE_DELETE(_userData);
}

bool Skill::init()
{
	if (!Node::init())
	{
		return false;
	}
	this->scheduleUpdate();
	setUserData(new SkillUserData(cd_time_, skill_category_));
	return true;
}

void Skill::setParent(Node* parent)
{
	Node::setParent(parent);
	setTimeParent(dynamic_cast<TimeCoefficient*>(parent));
}

bool Skill::cast(cocos2d::Layer* battle_layer, BaseObject* skill_parent, const cocos2d::Vec2& direction, BaseObject* skill_targer)
{
	if (battle_layer == nullptr)
		return false;
	if (cd_)
		return false;
	cd_ = true;
	cd_time_coefficient_ = getTimeCoefficient() > 0 ? getTimeCoefficient() : 1.0f;
	if (_userData != nullptr)
	{
		static_cast<SkillUserData*>(_userData)->setCDTime(cd_time_ / cd_time_coefficient_);
		EventCustom event(SKILL_EVENT);
		event.setUserData(_userData);
		_eventDispatcher->dispatchEvent(&event);
	}
	return true;
}

SkillCategory Skill::getSkillCategory()
{
	return skill_category_;
}

void Skill::update(float delta_time)
{
	Node::update(delta_time);
	if (cd_)
	{
		timer_ += delta_time*cd_time_coefficient_;
		if (timer_ >= cd_time_)
		{
			cd_ = false;
			timer_ = 0.0f;
		}
	}
}