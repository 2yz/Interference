#ifndef Player_H_
#define Player_H_

#include "BasePlane.h"

class Player : public BasePlane
{
public:
	CREATE_FUNC(Player);
	Player();
	virtual bool init() override;
	virtual void initMessage() override;
	virtual void onEnter() override;
	virtual void onDestroy() override;
	virtual void onContact(Message& message) override;
	float getTraceCoefficient();
	void setTraceCoefficient(float maxSpeed, float acceleration, float deltaTime);
	inline void updateMove(float deltaTime);
	inline void updateSkillCast(float deltaTime);
	virtual void update(float deltaTime) override;
protected:
	float _accelerationMagnitude;
private:
	float _traceCoefficient;
};

#endif /* Player_H_ */