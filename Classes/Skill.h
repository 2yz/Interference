#ifndef Skill_H_
#define Skill_H_

#include "cocos2d.h"
#include "BasePlane.h"

enum SkillCategory
{
	ATTACK,
	DEFENSE,
	SUPPORT,
	KILL
};

class Skill : public cocos2d::Node
{
public:
	Skill();
	virtual ~Skill();
	virtual bool init() override;
	virtual bool cast(cocos2d::Layer* battle_layer, BasePlane* skill_parent, const cocos2d::Vec2& direction, BaseObject* skill_targer = nullptr);
	SkillCategory getSkillCategory();
protected:
	float timer_;
	bool cd_;
	float cd_time_;
	SkillCategory skill_category_;
	virtual void update(float deltaTime) override;
};

#endif /* Skill_H_ */