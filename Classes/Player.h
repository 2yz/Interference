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
protected:
	float traceCoefficient;
	virtual void update(float deltaTime) override;
};

#endif /* Player_H_ */