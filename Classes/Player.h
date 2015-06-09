#ifndef Player_H_
#define Player_H_

#include "BasePlane.h"

class Player : public BasePlane
{
public:
	CREATE_FUNC(Player);
	Player();
	virtual bool init() override;
	// static Player* create(float x,float y);
	virtual void onEnter() override;
	float getTraceCoefficient();
	void setTraceCoefficient(float maxSpeed, float acceleration, float deltaTime);
	virtual void runSkill(const cocos2d::Vec2& velocity, SkillCategory skillCategory, int skillIndex = 0) override;
protected:
	float _accelerationMagnitude;
	virtual void update(float deltaTime) override;
private:
	float _traceCoefficient;
};

#endif /* Player_H_ */