#include "SkillUserData.h"

SkillUserData::SkillUserData(float cd_time, SkillCategory skill_category) : cd_time_(cd_time), skill_category_(skill_category)
{
}

float SkillUserData::getCDTime()
{
	return cd_time_;
}

void SkillUserData::setCDTime(float cd_time)
{
	cd_time_ = cd_time;
}

SkillCategory SkillUserData::getSkillCategory()
{
	return skill_category_;
}

void SkillUserData::setSkillCategory(SkillCategory skill_category)
{
	skill_category_ = skill_category;
}