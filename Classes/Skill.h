#ifndef Skill_H_
#define Skill_H_

#include "cocos2d.h"

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
	virtual bool run(const cocos2d::Vec2& velocity, cocos2d::Node* parent, cocos2d::Node* target, int bulletParent);
	SkillCategory getSkillCategory();
protected:
	float _timer;
	bool _CD;
	float _CDTime;
	SkillCategory _skillCategory;
	virtual void update(float deltaTime) override;
};

#endif /* Skill_H_ */