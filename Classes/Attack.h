#ifndef ATTACK_H_
#define ATTACK_H_

#include "Skill.h"

class Attack : public Skill
{
public:
	CREATE_FUNC(Attack);
	Attack();
	virtual bool run(const cocos2d::Vec2& velocity, cocos2d::Node* parent, cocos2d::Node* target, int bulletParent) override;
};

#endif /* ATTACK_H_ */