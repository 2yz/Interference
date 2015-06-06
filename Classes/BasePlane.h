#ifndef BASEPLANE_H_
#define BASEPLANE_H_

#include "BaseObject.h"

class BasePlane : public BaseObject
{
public:
	explicit BasePlane(float radius = 60.0f);
	virtual bool init() override;
	// static BasePlane* create();
protected:
	float linearDamping;
	float physicsRadius;
	float rotateVelocity; // degree per second
	virtual void update(float deltaTime) override;
};

#endif /* BASEPLANE_H_ */