#ifndef ATTACK_H_
#define ATTACK_H_

#include "Skill.h"

class Attack : public Skill
{
public:
	CREATE_FUNC(Attack);
	Attack();
	virtual void onEnter() override;
	virtual bool cast(cocos2d::Layer* battle_manager, BaseObject* skill_parent, const cocos2d::Vec2& direction, BaseObject* skill_targer = nullptr) override;
protected:
	int skill_parent_;
};

#endif /* ATTACK_H_ */