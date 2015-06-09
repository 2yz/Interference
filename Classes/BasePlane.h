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
	float _linearDamping;
	float _physicsRadius;
	float _rotateVelocity; // degree per second
	bool _beDestroyable; // Is destroyable when contact
	cocos2d::Vector<Skill*> _skillVec;
	virtual void update(float deltaTime) override;
};

#endif /* BASEPLANE_H_ */