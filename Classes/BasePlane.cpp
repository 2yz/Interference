#include "BasePlane.h"
#include "ConfigUtil.h"

USING_NS_CC;

BasePlane::BasePlane(float radius) :BaseObject(), physics_radius_(radius), rotate_velocity_(180.0f)
{
}

BasePlane::~BasePlane()
{
	skill_vector_.clear();
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

void BasePlane::addSkill(Skill* skill)
{
	if (skill_vector_.empty())
		skill_vector_.reserve(4);
	skill_vector_.pushBack(skill);
	addChild(skill);
}

void BasePlane::castSkill(cocos2d::Layer* battle_layer, const cocos2d::Vec2& direction, BaseObject* skill_targer)
{
	if (battle_layer == nullptr)
		return;
	auto skill_iterator = skill_vector_.begin();
	if (skill_iterator != skill_vector_.end())
		(*skill_iterator)->cast(battle_layer, this, direction, skill_targer);
}

void BasePlane::castSkill(cocos2d::Layer* battle_layer, const cocos2d::Vec2& direction, int skill_index, BaseObject* skill_targer)
{
	if (battle_layer == nullptr)
		return;
	if (skill_index < skill_vector_.size())
		skill_vector_.at(skill_index)->cast(battle_layer, this, direction, skill_targer);
}

void BasePlane::castSkill(cocos2d::Layer* battle_layer, const cocos2d::Vec2& direction, SkillCategory skill_category, BaseObject* skill_targer)
{
	if (battle_layer == nullptr)
		return;
	for (auto skill : skill_vector_)
	{
		if (skill->getSkillCategory() == skill_category)
		{
			skill->cast(battle_layer, this, direction, skill_targer);
			break;
		}
	}
}

void BasePlane::update(float delta_time)
{
	BaseObject::update(delta_time);
}
