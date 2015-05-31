#ifndef PLAYERPLANE_H_
#define PLAYERPLANE_H_

#include "BasePlane.h"

class PlayerPlane : public BasePlane
{
public:
	PlayerPlane();
	virtual bool init() override;
	// static PlayerPlane* create();
	CREATE_FUNC(PlayerPlane);
	virtual void update(float deltaTime) override;
	float getTraceCoefficient();
protected:
	const int initHP;
	const float acceleration;
	const float maxSpeed;
	const float traceCoefficient;
	float lastPositionX = 0;
	float lastPositionY = 0;
};

#endif /* PLAYERPLANE_H_ */