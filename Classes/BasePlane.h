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
	virtual void runSkill(const cocos2d::Vec2& velocity, SkillCategory skillCategory, int skillIndex = 0);
	// static BasePlane* create();
protected:
	float linearDamping;
	float physicsRadius;
	float rotateVelocity; // degree per second
	bool _beDestroyable;
	cocos2d::Vector<Skill*> _skillVec;
	virtual void update(float deltaTime) override;
};

#endif /* BASEPLANE_H_ */