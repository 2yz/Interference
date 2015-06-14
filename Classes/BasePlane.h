#ifndef BASEPLANE_H_
#define BASEPLANE_H_

#include "BaseObject.h"
#include "Skill.h"

class BasePlane : public BaseObject
{
public:
	explicit BasePlane(float radius = 60.0f);
	virtual ~BasePlane();
	virtual bool init() override;
	virtual void addSkill(Skill* skill);
	virtual void castSkill(cocos2d::Layer* battle_layer, const cocos2d::Vec2& direction, BaseObject* skill_targer = nullptr);
	virtual void castSkill(cocos2d::Layer* battle_layer, const cocos2d::Vec2& direction, int skill_index, BaseObject* skill_targer = nullptr);
	virtual void castSkill(cocos2d::Layer* battle_layer, const cocos2d::Vec2& direction, SkillCategory skill_category, BaseObject* skill_targer = nullptr);
	//virtual void castSkill(const cocos2d::Vec2& velocity, SkillCategory skillCategory, int skillIndex = 0);
	// static BasePlane* create();
protected:
	float linear_damping_;
	float physics_radius_;
	float rotate_velocity_; // degree per second
	cocos2d::Vector<Skill*> skill_vector_;
	virtual void update(float deltaTime) override;
};

#endif /* BASEPLANE_H_ */