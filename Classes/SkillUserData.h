#ifndef SKILLUSERDATA_H_
#define SKILLUSERDATA_H_

#include "Skill.h"

class SkillUserData {
public:
	SkillUserData(float cd_time, SkillCategory skill_category);
	float getCDTime();
	void setCDTime(float cd_time);
	SkillCategory getSkillCategory();
	void setSkillCategory(SkillCategory skill_category);
protected:
	float cd_time_;
	SkillCategory skill_category_;
};


#endif /* SKILLUSERDATA_H_ */